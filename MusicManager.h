//Adam Tammariello
//Final Project
//4/25/2015
#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <cstdlib>
#include <vector>
#include <string>

struct Song{
    std::string title;
    std::string artist;
    std::string genre;
    int numPlays;
    int popularity;
    Song *next;

    Song(){};

    Song(std::string songTitle, std::string songArtist, std::string songGenre, int songPopularity)
    {
        title = songTitle;
        artist = songArtist;
        genre = songGenre;
        popularity = songPopularity;
        numPlays = 0;
    }

};

struct Playlist{
    std::string name;
    std::vector<Song *> songs;
    Playlist *next;

    Playlist(){};

    Playlist(std::string playlistName)
    {
        name = playlistName;
    }

};

class MusicManager
{
    public:
        MusicManager(int);
        ~MusicManager();
        void addSongToInventory(std::string songTitle, std::string artist, std::string genre, int songPopularity);
        Song* findSongInInventory(std::string songTitle, int *index);
        void deleteSongFromInventory(std::string songTitle); //Not a menu  option. Is tested in Driver. Use for Possible Extension.
        void printInventory();
        void createPlaylist(std::string playlistName);
        void deletePlaylist(std::string playlistName);
        void addSongToPlaylist(std::string songTitle, std::string playlistName);
        void deleteSongFromPlaylist(std::string songTitle, std::string playlistName);
        Song *findSongInPlaylist(std::string songTitle, std::string playlistName);
        void printPlaylist(std::string playlistName);
        Playlist *findPlaylist(std::string name, int *index);
        void sortPlaylistbyGenre(std::string playlistName);
        void sortPlaylistbyPopularity(std::string playlistName);
    protected:
    private:
        int hashSum(std::string key, int size);
        void quickSortPopularity(std::vector<Song *> *arr, int left, int right);
        void quickSortGenre(std::vector<Song *> *arr, int left, int right);
        std::vector<Song *> songInventory;
        std::vector<Playlist *> playlists;
        int tableSize;

};

#endif // MUSICMANAGER_H
