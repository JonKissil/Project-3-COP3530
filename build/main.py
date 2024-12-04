import pandas as pd
import numpy as np
import sys

if __name__ == "__main__":
    df = pd.read_csv("filtered.csv")
    df.drop('year', inplace=True, axis=1)
    df.drop('language_cld3', inplace=True, axis=1)
    df.drop('language_ft', inplace=True, axis=1)
    df.drop('views', inplace=True, axis=1)

    artist = sys.argv[1]
    songname = sys.argv[2]

    #find user song
    songinfo = df.loc[df['title'] == songname]
    songinfo = songinfo.loc[songinfo['artist'] == artist]

    # get song metadata
    songinfo = songinfo.reset_index()
    lang = songinfo.at[0, 'language']
    tag = songinfo.at[0, 'tag']
    id = songinfo.at[0, 'id']

    # chop down list to relevant songs (5000 random songs within the same genre + our choice)
    df = df[df['language'].isin([lang])]
    df = df[df['tag'].isin([tag])].sample(n = 5000, replace = True)
    df = pd.concat([df, songinfo], ignore_index = True)

    # clear out punctuation and bag words
    df['bag'] = df.lyrics.map(
        lambda t: t.replace(')', '').replace('(', '').replace(',', '').replace('!', '').replace('?', '').replace('.', '').replace("\n", " ").lower().split())
    df['len'] = df.bag.map(len)

    # remove unnecessary columns and create df with unique song ids matched to their corresponding lyrics
    df2 = df.groupby('id')
    df2 = df2.bag.aggregate(lambda bag: [a for b in bag.values for a in b])

    # calculate individual lyric frequencies for each song
    frequencies = df2.apply(lambda bag: pd.Series(bag).value_counts())

    # calculate document frequencies - or the amount of songs each lyric appears in
    document_freq = frequencies.count()

    # cross multiply document frequency with lyric frequency
    n = float(len(frequencies))
    rarity = np.log(n / document_freq)
    net = frequencies * rarity

    # normalize and calculate cosine similarity
    prenormalized = np.sqrt((net*net).sum(axis = 1))
    normalized = net.divide(prenormalized, axis = 0)
    normalized = normalized.fillna(0)

    cosine = normalized.dot(normalized.transpose())

    # get our results
    results = cosine[id]
    closest_songs = results.nlargest(20)
    ids = closest_songs.index.values
    final_output = []
    for i in range(len(ids)):
        title_frame = df.loc[df['id'] == ids[i]]
        title_frame = title_frame.reset_index()
        artist = title_frame.at[0, 'artist']
        name = title_frame.at[0, 'title']
        final_output.append((artist, name))

    file = open("results.txt", "w")

    for i in range(len(final_output)):
        final_output_string = final_output[i][0].replace('\u200b', '') + " - " + final_output[i][1].replace('\u200b', '') + "\n"
        file.write(final_output_string)

    print(cosine.head())
