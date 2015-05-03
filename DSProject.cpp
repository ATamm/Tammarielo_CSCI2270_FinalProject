//Adam Tammariello
//Final Project
//4/25/2015
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>
#include "MusicManager.h"


using namespace std;


int main(int argc, char* argv[])
{
	string value="";
	string nextline="";
	ifstream infile("SomeSongs.txt"); //file name hardcoded
    int selection=0;
	string input="";
    MusicManager *musicManager = new MusicManager(10);  // create new music maanger


     while (getline(infile, nextline)) { // read each line in the file

    	 istringstream line(nextline);  // create a stringstream out of line
    	 int popularity=0;
    	 string title="";
    	 string artist="";
    	 string genre="";

    	 // get comma separate values in order from line

    	 getline(line, value, ',');
    	 title = value;
    	 getline(line, value, ',');
    	 artist = value;
    	 getline(line, value, ',');
    	 genre = value;
    	 getline(line, value, ',');
    	 popularity = atoi(value.c_str());

     	 musicManager->addSongToInventory(title, artist, genre, popularity); // add new song

     }

     while (selection != 13) { // loop until user selects 11
     		cout<<"Welcome to the music manager! Please make a selection..."<<endl;
     		cout<<"1. View the music inventory"<<endl;
     		cout<<"2. Find a song in the inventory"<<endl;
     		cout<<"3. Create a playlist"<<endl;
     		cout<<"4. Add a song to your playlist"<<endl;
     		cout<<"5. Find a song in your playlist"<<endl;
     		cout<<"6. Delete a song from your playlist"<<endl;
     		cout<<"7. Print your playlist"<<endl;
     		cout<<"8. Delete your playlist"<<endl;
     		cout<<"9. Sort your playlist by popularity"<<endl;
     		cout<<"10. Sort your playlist by genre"<<endl;
     		cout<<"11. Like a song"<<endl;
     		cout<<"12. Dislike a song"<<endl;
     		cout<<"13. Quit"<<endl;
     		getline(cin, input);
     		selection = atoi(input.c_str()); // get user selection
     		if (selection == 1) { // view inventory
     			musicManager->printInventory();
     		} else if (selection == 2) { //find song in inventory
     			cout<<"Enter song title:"<<endl;
     			string title="";
     			getline(cin, title);
     			int index;
     			Song *foundSong;
     			foundSong = musicManager->findSongInInventory(title, &index);
     			if (foundSong == NULL) {
     				cout<<"Sorry, we don't have that song"<<endl;
     			} else {
     				cout<<foundSong->title<<","<<foundSong->artist<<","<<foundSong->genre<<","<<foundSong->popularity<<endl;
     			}
     		} else if (selection == 3) { // create a playlist
     			cout<<"Enter a name for your playlist:"<<endl;
     			string name="";
     			getline(cin, name);
     			int index;
     			Playlist *foundPlaylist = musicManager->findPlaylist(name, &index);
     			if (foundPlaylist != NULL) {
     				cout<<"Sorry, that playlist name is already taken"<<endl;
     			} else {
     				musicManager->createPlaylist(name);
     			}
     		}  else if (selection == 4) { // add song to playlist
     			cout<<"Enter song title:"<<endl;
     			string title="";
     			getline(cin, title);
     			cout<<"Enter playlist name:"<<endl;
     			string playlist="";
     			getline(cin, playlist);
     			int index;
     			Playlist *foundPlaylist = musicManager->findPlaylist(playlist, &index);
     			if (foundPlaylist == NULL) {
     				cout<<"Sorry, can't find a playlist with that name"<<endl;
     			} else {
     				Song *foundSong;
     				foundSong = musicManager->findSongInInventory(title, &index);
     				if (foundSong == NULL) {
     					cout<<"Sorry, we don't have that song"<<endl;
     				} else {
     					musicManager->addSongToPlaylist(title, playlist);
     				}
     			}
           	} else if (selection == 5) { // find a song in playlist
           		cout<<"Enter song title:"<<endl;
           		string title="";
           		getline(cin, title);
           		cout<<"Enter playlist name:"<<endl;
           		string playlist="";
           		getline(cin, playlist);
           		int index;
           		Playlist *foundPlaylist = musicManager->findPlaylist(playlist, &index);
           		if (foundPlaylist == NULL) {
           			cout<<"Sorry, can't find a playlist with that name"<<endl;
           		} else {
           			Song *foundSong;
           			foundSong = musicManager->findSongInPlaylist(title, playlist);
           			if (foundSong == NULL) {
           				cout<<"Sorry, that song isn't in your playlist"<<endl;
           			} else {
           				cout<<foundSong->title<<","<<foundSong->artist<<","<<foundSong->genre<<endl;
           			}
           		}
           	}  else if (selection == 6) { // delete a song from  playlist
     			cout<<"Enter song title:"<<endl;
     			string title="";
     			getline(cin, title);
     			cout<<"Enter playlist name:"<<endl;
     			string playlist="";
     			getline(cin, playlist);
     			int index;
     			Playlist *foundPlaylist = musicManager->findPlaylist(playlist, &index);
     			if (foundPlaylist == NULL) {
     				cout<<"Sorry, can't find a playlist with that name"<<endl;
     			} else {
     				Song *foundSong;
     				foundSong = musicManager->findSongInPlaylist(title, playlist);
     				if (foundSong == NULL) {
     					cout<<"Sorry, that song isn't in your playlist"<<endl;
     				} else {
     					musicManager->deleteSongFromPlaylist(title, playlist);
     				}
     			}
           	} else if (selection == 7) { // print playlist
     			cout<<"Enter playlist name:"<<endl;
     			string playlist="";
     			getline(cin, playlist);
     			int index;
     			Playlist *foundPlaylist = musicManager->findPlaylist(playlist, &index);
     			if (foundPlaylist == NULL) {
     				cout<<"Sorry, can't find a playlist with that name"<<endl;
     			} else {
     				musicManager->printPlaylist(playlist);
     			}
           	} else if (selection == 8) { // delete  playlist
           		cout<<"Enter playlist name:"<<endl;
           		string playlist="";
           		getline(cin, playlist);
           		int index;
           		Playlist *foundPlaylist = musicManager->findPlaylist(playlist, &index);
           		if (foundPlaylist == NULL) {
           			cout<<"Sorry, can't find a playlist with that name"<<endl;
           		} else {
           			musicManager->deletePlaylist(playlist);
           		}
           	} else if (selection == 9) { // sort  playlist by poularity
           		cout<<"Enter playlist name:"<<endl;
           		string playlist="";
           		getline(cin, playlist);
           		int index;
           		Playlist *foundPlaylist = musicManager->findPlaylist(playlist, &index);
           		if (foundPlaylist == NULL) {
           			cout<<"Sorry, can't find a playlist with that name"<<endl;
           		} else {
           			musicManager->sortPlaylistbyPopularity(playlist);
           		}

           	} else if (selection == 10) { // sort  playlist by genre
           		cout<<"Enter playlist name:"<<endl;
           		string playlist="";
           		getline(cin, playlist);
           		int index;
           		Playlist *foundPlaylist = musicManager->findPlaylist(playlist, &index);
           		if (foundPlaylist == NULL) {
           			cout<<"Sorry, can't find a playlist with that name"<<endl;
           		} else {
           			musicManager->sortPlaylistbyGenre(playlist);
           		}
           	} else if (selection == 11) {
                cout<<"Enter song title:"<<endl;
     			string title="";
     			getline(cin, title);
     			int index;
     			Song *foundSong;
     			foundSong = musicManager->likeSong(title, &index);
     			if (foundSong == NULL) {
     				cout<<"Sorry, we don't have that song"<<endl;
     			} else {
     				cout<<foundSong->title<<","<<foundSong->artist<<","<<foundSong->genre<<","<<foundSong->popularity<<","<<foundSong->likes<<" like(s)"<<endl;
     			}
           	}
           	else if (selection == 12) {
                cout<<"Enter song title:"<<endl;
     			string title="";
     			getline(cin, title);
     			int index;
     			Song *foundSong;
     			foundSong = musicManager->dislikeSong(title, &index);
     			if (foundSong == NULL) {
     				cout<<"Sorry, we don't have that song"<<endl;
     			} else {
     				cout<<foundSong->title<<","<<foundSong->artist<<","<<foundSong->genre<<","<<foundSong->popularity<<","<<foundSong->likes<<" like(s)"<<endl;
     			}
           	}

     }
        cout<<"Thanks for visiting"<<endl;
     	delete musicManager;

     	return 0;
}


