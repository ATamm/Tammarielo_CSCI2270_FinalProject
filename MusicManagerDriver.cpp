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

int main ()
{

	string musicFilename = "SomeSongs.txt";
	string value="";
	string nextline="";
	ifstream infile("SomeSongs.txt");
	int selection=0;
	string input="";
	MusicManager *musicManager = new MusicManager(10);  // create new music manager
	int index;


	while (getline(infile, nextline)) { // read each line in the file

	 	 istringstream line(nextline);  // create a stringstream out of line
	   	 int ranking=0;
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
	     ranking = atoi(value.c_str());

	      musicManager->addSongToInventory(title, artist, genre, ranking); // add new node

	}

	// call the differnt MusicManager functions passing parameters

	cout<<">>>>>Print Inventory"<<endl;
    musicManager->printInventory();
    cout<<">>>>>Find a Song in inventory"<<endl;
    Song *song =  musicManager->findSongInInventory("Surrender", &index);
    if (song != NULL) {
    	cout<<song->title<<","<<song->artist<<","<<song->genre<<","<<song->popularity<<endl;
    }
    musicManager->createPlaylist("playlist1");
    musicManager->addSongToPlaylist("Revolution", "playlist1");
    musicManager->deleteSongFromInventory("Heroes and Villians");
    musicManager->printInventory();
    musicManager->addSongToPlaylist("Surrender", "playlist1");
    musicManager->addSongToPlaylist("Ain't That A Kick In The Head", "playlist1");
    cout<<">>>>>Print playlist"<<endl;
    musicManager->printPlaylist("playlist1");
    musicManager->sortPlaylistbyPopularity("playlist1");
    cout<<">>>>>Print playlist after sorted by popularity"<<endl;
    musicManager->printPlaylist("playlist1");
    musicManager->sortPlaylistbyGenre("playlist1");
    cout<<">>>>>Print playlist after sorted by genre"<<endl;
    musicManager->printPlaylist("playlist1");
	musicManager->createPlaylist("playlist2");
	musicManager->addSongToPlaylist("Revolution", "playlist2");
	cout<< "PrintPlaylist"<< endl;
	musicManager->printPlaylist("playlist2");
	musicManager->deleteSongFromPlaylist("Revolution","playlist2");
	musicManager->deletePlaylist("playlist2");
	cout<<"deleted playlist"<<endl;
	Song *playlistsong =  musicManager->findSongInPlaylist("Revolution", "playlist1");
	if ( playlistsong != NULL){
		cout<<song->title<<","<<song->artist<<","<<song->genre<<","<<song->popularity<<endl;
    }
    Playlist *playlist = musicManager->findPlaylist("playlist1", &index);
    if (playlist != NULL){
		cout<< playlist->name <<endl;
	}
	musicManager->sortPlaylistbyGenre("playlist1");
	musicManager->printPlaylist("playlist1");
	musicManager->sortPlaylistbyPopularity("playlist1");
	musicManager->printPlaylist("playlist1");
		
}
