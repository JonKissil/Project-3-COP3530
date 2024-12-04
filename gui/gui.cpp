//
// Created by Maddie on 11/25/2024.
//

#include "gui.h"
#include <gtk/gtk.h>
#include <iostream>


// it doesnt compile without having this here ¯\_(ツ)_/¯
// static members of the gui class have to be inited with null
//===================================================
GUI* GUI::instance = nullptr;
std::string* GUI::artistPtr = nullptr;
std::string* GUI::songPtr = nullptr;
std::vector<std::string>* GUI::outputDisplayList = nullptr;
std::vector<std::vector<std::string>>* GUI::groupedList = nullptr;
std::function<void()> GUI::externalFunction = nullptr;
GObject* GUI::artistEntry = nullptr;
GObject* GUI::songEntry = nullptr;
GtkWidget* GUI::view1 = nullptr;
GtkWidget* GUI::view2 = nullptr;
GtkWidget *GUI::listView = nullptr;
int GUI::pageNumber = 0;
//===================================================


// gui class instance handling
//==================================
GUI::GUI() {
    app = gtk_application_new ("org.gtk.Similyrically", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
}

GUI &GUI::getInstance() {
    if(!instance){
        instance = new GUI();
    }
    return *instance;
}
//==================================


// aux functions
//==================================
/**
 * set what function to run when button is pressed
 * @param func function to run
 */
void GUI::setSearchButtonFunction(std::function<void()> func) {
    externalFunction = func;
}

/**
 * Where to put user inputted string into
 * just give a pointer to the string that the artistPtr
 * should be written to
 * @param artistPtr
 */
void GUI::setInputPtrs(std::string *artistPtr, std::string *songPtr) {
    this->artistPtr = artistPtr;
    this->songPtr = songPtr;
}

/**
 *  Where to get the list data that is displayed after hitting run
 *  Pass a pointer to the data you want to display
 * @param output
 */
void GUI::setOutputListPtr(std::vector<std::string> *output) {
    outputDisplayList = output;
}

//==================================



// running and closing gtk app
//==================================
int GUI::run() {
    int status = g_application_run (G_APPLICATION (app), 0, {});
    safeClose();
    return status; // running the app returns an error code. just pass back to main() return
}

void GUI::safeClose() {
    g_object_unref (app);
}
//==================================



// helper
void GUI::createGroupedList(size_t group_size) {
    if(groupedList== nullptr){
        groupedList = new std::vector<std::vector<std::string>>;
    }
    (*groupedList).clear();

    for (size_t i = 0; i < (*outputDisplayList).size(); i += group_size) {
        std::vector<std::string> group;
        for (size_t j = i; j < i + group_size && j < (*outputDisplayList).size(); ++j) {
            group.push_back((*outputDisplayList)[j]);
        }
        (*groupedList).push_back(group);
    }
}

void GUI::nextButton(){
    if(pageNumber < (*groupedList).size()-1){
        pageNumber++;
        refreshList();
    }else{
        refreshList();
    }
}

void GUI::backButton() {
    if(pageNumber == 0){
        refreshList();
    }else{
        pageNumber--;
        refreshList();
    }
}


void GUI::refreshList() {
    for (int i = 0; i < numItems; i++) {
        GtkListBoxRow *row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(listView), i);
        if(i < (*groupedList)[pageNumber].size()){
            if(row == nullptr){
                row = GTK_LIST_BOX_ROW(gtk_list_box_row_new());
                GtkWidget *label = gtk_label_new(g_strdup(((*groupedList)[pageNumber])[i].c_str()));
                gtk_list_box_row_set_child(row, label);
                gtk_list_box_row_set_selectable(row, false);
                gtk_list_box_row_set_activatable(row, false);

                gtk_list_box_insert(GTK_LIST_BOX(listView), GTK_WIDGET(row), -1); // Insert at the end
            }else {
                gtk_label_set_label(GTK_LABEL(gtk_list_box_row_get_child(row)), ((*groupedList)[pageNumber])[i].c_str());
            }
        }else{
            if(row != nullptr){
                gtk_label_set_label(GTK_LABEL(gtk_list_box_row_get_child(row)), "");
            }
        }
    }
}


void GUI::searchButtonFunctionCaller() {

    // get entry aBuffer and grab aText from aBuffer
    GtkEntryBuffer *aBuffer = gtk_entry_get_buffer(GTK_ENTRY(artistEntry));
    const gchar *aText = gtk_entry_buffer_get_text(aBuffer);
    // convert c style string to a normal string
    // check if string is empy
    std::string artistString = std::string(aText);

    GtkEntryBuffer *sBuffer = gtk_entry_get_buffer(GTK_ENTRY(songEntry));
    const gchar *sText = gtk_entry_buffer_get_text(sBuffer);
    std::string songString = std::string(sText);

    if(artistString.empty() || songString.empty()){
        return;
    }

    // set pointed artistPtr data
    *artistPtr = artistString;
    *songPtr = songString;

    // call external function
    externalFunction();

    // create grouped list
    createGroupedList(numItems);

    gtk_list_box_set_show_separators(GTK_LIST_BOX(listView), true);

    // load in list
    pageNumber = 0;
    refreshList();


    gtk_widget_set_visible(view1, false);
    gtk_widget_set_visible(view2, true);
}

void GUI::returnButton() {
    gtk_widget_set_visible(view2, false);
    gtk_widget_set_visible(view1, true);
}



// setting up gtk app
//==================================
void GUI::activate(GtkApplication *app, gpointer user_data) {

    // Set up builder from ui file
    GtkBuilder *builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "./builder.ui", NULL);
    
    // set up objects to save from builder to use later
    //+++++++++++++++++
    view1 = GTK_WIDGET(gtk_builder_get_object(builder, "view1"));

    view2 = GTK_WIDGET(gtk_builder_get_object(builder, "view2"));

    listView = GTK_WIDGET(gtk_builder_get_object(builder, "v2_list"));
    //+++++++++++++++++

    // Connect signal handlers
    //+++++++++++++++++++++++
    // grab window and set up app
    GObject *window = gtk_builder_get_object (builder, "window");
    gtk_window_set_application (GTK_WINDOW (window), app);

    // View 1
    //****************
    // set up button signal handling
    GObject *button = gtk_builder_get_object (builder, "v1_button1");
    g_signal_connect (button, "clicked", G_CALLBACK(searchButtonFunctionCaller), NULL);

    // when 'Enter' is hit in the text entry do the same as button ^
    artistEntry = gtk_builder_get_object(builder, "v1_artistEntry");
    g_signal_connect (artistEntry, "activate", G_CALLBACK(searchButtonFunctionCaller), NULL);
    songEntry = gtk_builder_get_object(builder, "v1_songEntry");
    g_signal_connect (songEntry, "activate", G_CALLBACK(searchButtonFunctionCaller), NULL);
    //****************

    // View 2
    //****************
    button = gtk_builder_get_object (builder, "v2_restartButton");
    g_signal_connect (button, "clicked", G_CALLBACK(returnButton), NULL);

    button = gtk_builder_get_object (builder, "v2_backButton");
    g_signal_connect (button, "clicked", G_CALLBACK(backButton), NULL);

    button = gtk_builder_get_object (builder, "v2_nextButton");
    g_signal_connect (button, "clicked", G_CALLBACK(nextButton), NULL);
    //****************

    gtk_widget_set_visible (GTK_WIDGET (window), TRUE);
    //+++++++++++++++++++++++


    gtk_widget_set_visible(view2, false);
    gtk_widget_set_visible(view1, true);


    // builder no longer needed
    g_object_unref (builder);
}
//==================================
