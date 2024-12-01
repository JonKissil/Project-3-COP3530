//
// Created by Maddie on 11/25/2024.
//

#ifndef GTK_TEST_GUI_H
#define GTK_TEST_GUI_H

#include <gtk/gtk.h>
#include <string>
#include <vector>
#include <functional>

class GUI{

    //==================================
    GUI();
    static GUI* instance;

    GtkApplication *app;
    static void activate(GtkApplication *app, gpointer user_data);
    //==================================


    // function that will be assigned to button
    static std::function<void()> externalFunction;

    // where to write inputted string
    static std::string *inputString;

    // what will be displayed on the output list
    static std::vector<std::string> *outputDisplayList;

    static std::vector<std::vector<std::string>> *groupedList;

    // GUI objects
    //=========
    static GObject *textEntry;

    static GtkWidget *view1;
    static GtkWidget *view2;

    static GtkWidget *listView;
    //=========


    //helpers
    static void createGroupedList(size_t group_size);
    static int pageNumber;

    static void backButton();
    static void nextButton();
    static void refreshList();

    // number of items to display on the list
    static const int numItems = 10;
public:
    // instance handling
    static GUI& getInstance();

    static void returnButton();

    // set what the search button does
    void setSearchButtonFunction(std::function<void()> func);
    static void searchButtonFunctionCaller();

    // set where to write input string
    // and set where to read out from
    void setInputPtr(std::string *input);
    void setOutputListPtr(std::vector<std::string> *output);

    // used for starting and closing gui
    int run();
    void safeClose();


};


#endif //GTK_TEST_GUI_H
