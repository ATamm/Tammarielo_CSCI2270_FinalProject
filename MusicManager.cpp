//Adam Tammariello
//Final Project
//4/25/2015
#include "MusicManager.h"
#include <iostream>


using namespace std;

MusicManager::MusicManager(int size) {
	tableSize = size;
	for (int i=0; i<tableSize; i++) {  // initialize inventory and playlist hash tables to NULL pointers
		songInventory.push_back(NULL);
		playlists.push_back(NULL);
	}
}

MusicManager::~MusicManager() {

}
/*Prototype:
void musicManager:: printInventory()
Description:
acesses all entries in the inventory vector. It prints the song and any linked list in that vector loccation.
How To Call:
musicManager->printInventory()
Pre-Condition:
assumes inventory is populated with Songs
Post-Condition:
no post condition
*/
void MusicManager::printInventory() {
	for (int i=0; i<songInventory.size(); i++) { // loop through hash table
		Song *song=songInventory[i];
		while (song != NULL) {  // print all songs in chain
			cout<<song->title<<","<<song->artist<<","<<song->genre<<","<<song->popularity<<endl;
			song = song->next;
		}
	}
}
/*Prototype:
 void addSongToInventory(string, string, string, int)
Description:
This method takes the parameters from the file, creates a song struct, and adds to the inventory hash table
how to call:
musicManager->addSongToInventory("Revolution", "Beatles", "Rock", 20);
pre-conditions:
no conditions
post conditions:
song added to inventory
*/
void MusicManager::addSongToInventory(std::string songTitle, std::string artist, std::string genre, int songPopularity){
	Song *newSong = new Song(songTitle, artist, genre, songPopularity);
	newSong->next = NULL;
	int hash = hashSum(songTitle, tableSize);  // get the hash
	if (songInventory[hash] == NULL) {  // this is the first song at this index
		songInventory[hash] = newSong;
	} else {  // collision
		if (newSong->title <= songInventory[hash]->title) { // if new title is less, add as head
			newSong->next = songInventory[hash];
			songInventory[hash] = newSong;
		} else {
			Song *nextSong = songInventory[hash]->next;
			Song *prevSong = songInventory[hash];
			while (nextSong != NULL) {       // loop until hit end of collision chain
				if (newSong->title <= nextSong->title) {   // add new song if less
					prevSong->next = newSong;
					newSong->next = nextSong;
					return;
				} else {                       // go to next song in chain
					prevSong = nextSong;
					nextSong = nextSong->next;
				}
			}  // song wasn't added, add to end of list
			prevSong->next = newSong;
		}
	}
}
/*Prototype:
Song * musicManager:: findSongInInventory(string, *int)
Description:
this method takes the the title of a song and generates a hash key and looks for a song title in the inventory hash table
How to Call
Song *song = musicManager->findSongInInventory("Revolution", &index)
Pre-Conditions:
Assumes the song exists in inventory.
Post-Condition:
Returns the pointer to the song if its in the inventory.
*/

Song* MusicManager::findSongInInventory(std::string songTitle, int *index) {
	int hash = hashSum(songTitle, tableSize);  // get the hash
	*index = hash;
	if (songInventory[hash] == NULL) {
		return NULL;
	} else {
		if (songInventory[hash]->title == songTitle) {  // song is first in chain
			return songInventory[hash];
		} else {
			Song *nextSong = songInventory[hash]->next;
			while (nextSong != NULL) {            // loop through all songs in chain
				if (nextSong->title == songTitle) {
					return nextSong;
				} else {
					nextSong = nextSong->next;
				}
			}
			return nextSong;     // song not found, return null
		}
	}
}
/*Prototype:
void musicManager:: deleteSongFromInventory(string)
Description:
creates a Hash of the song title, finds the song in  the inventory, and delete from the hash table.
Pre-Condition:
Assumes song is in inventory
Post-Condition:
song is deleted from inventory hash table. All pointers are properly adjusted.
*/

void MusicManager::deleteSongFromInventory(std::string songTitle) {
	Song *songToDelete;
	int index;
	songToDelete = findSongInInventory(songTitle,&index);   // see if song is in table
	if (songToDelete == NULL) {             // song not in table
		cout<<"not found"<<endl;
	} else {
		Song *nextSong = songToDelete->next;   // found the song, save this song's next pointer
		if (songInventory[index]->title == songToDelete->title) {  // song to delete was head of chain
			songInventory[index] = nextSong;         // next song is now head
		} else {
			Song *prevSong = songInventory[index];  // keep track of previous sonsg
			while (prevSong->next->title != songToDelete->title) { // loop until find song to delete
				prevSong = prevSong->next;
			}
			prevSong->next = nextSong;  // set previous->next to next song
		}
		delete songToDelete;             // delete song
	}
}
/*Prototype:
void musicManager::createPlaylist(string)
Description:
Creates a Playlist structure and assigns the name, and then gets a hash code for that name and adds the playlist to the Playlists hash table.
How To Call:
musicManager->createPlaylist(myPlaylist);
Pre-Condition:
no preconditions
Post-Conditions:
a playlist with a specified names is added to Playlists hash table.
*/
void MusicManager::createPlaylist(std::string playlistName) {
	Playlist *newPlaylist = new Playlist(playlistName);
	newPlaylist->next = NULL;
	int hash = hashSum(playlistName, tableSize);  // get the hash
	if (playlists[hash] == NULL) {  // this is the first song at this index
		playlists[hash] = newPlaylist;
	} else {  // collision
		if (newPlaylist->name <= playlists[hash]->name) { // if new title is less, add as head
			newPlaylist->next = playlists[hash];
			playlists[hash] = newPlaylist;
		} else {
			Playlist *nextPlaylist = playlists[hash]->next;
			Playlist *prevPlaylist = playlists[hash];
			while (nextPlaylist != NULL) {       // loop until hit end of collision chain
				if (newPlaylist->name <= nextPlaylist->name) {   // add new song if less
					prevPlaylist->next = newPlaylist;
					newPlaylist->next = nextPlaylist;
					return;
				} else {                       // go to next song in chain
					prevPlaylist = nextPlaylist;
					nextPlaylist = nextPlaylist->next;
				}
			}  // song wasn't added, add to end of list
			prevPlaylist->next = newPlaylist;
		}
	}
}
/*Prototype:
void musicManager:: deletePlaylist(string)
Description:
creates a hash for the playlist name and deletes the playlist from the Playlist hash table
How To Call:
musicManager->deletePlaylist(myPlaylist)
Pre-Condition:
assumes playlist has been added to the Playlists hash table
Post-Condition:
playlist removed from playlist hash table.
*/
void MusicManager::deletePlaylist(std::string playlistName) {
	Playlist *playlistToDelete;
	int index;
	playlistToDelete = findPlaylist(playlistName,&index);   // see if playlist is in table
	if (playlistToDelete == NULL) {             // playlist not in table
		cout<<"not found"<<endl;
	} else {
		Playlist *nextPlaylist = playlistToDelete->next;   // found the playlist, save this playlist's next pointer
		if (playlists[index]->name == playlistToDelete->name) {  // playlist to delete was head of chain
			playlists[index] = nextPlaylist;         // next playlist is now head
		} else {
			Playlist *prevPlaylist = playlists[index];  // keep track of previous playlist
			while (prevPlaylist->next->name != playlistToDelete->name) { // loop until find playlist to delete
				prevPlaylist = prevPlaylist->next;
			}
			prevPlaylist->next = nextPlaylist;  // set previous->next to next playlist
		}
		delete playlistToDelete;             // delete playlist
	}

}
/*Prototype:
void musicManager:: addSongToPlaylist(string, string)
Description:
finds the playlist and finds the song in the inventory, then adds a pointer to the song's vector for the playlist for the specific song.
How To CallL
musicManager->addSongToPlaylist("Revolution", "myPlaylist")
Pre-Conditions:
assumes songs are in inventory, and that a playlist is created
Post-Condition:
song pointer added to song's vector of the playlist
*/
void MusicManager::addSongToPlaylist(std::string songTitle, std::string playlistName) {
	int index;
	Song *newSong = findSongInInventory(songTitle, &index);
	Playlist *playlist = findPlaylist(playlistName, &index);
	if ((newSong != NULL) && (playlist != NULL)) {
		for (int i=0; i < playlist->songs.size(); i++) {
			Song *nextSong = playlist->songs[i];
			if (newSong->title <= nextSong->title) {
				playlist->songs.insert(playlist->songs.begin()+i, newSong);
				return;
			}
		}
		playlist->songs.push_back(newSong);
	}
}
/*Prototype:
void musicManager:: deleteSongFromPlaylist(string, string)
Description:
finds the playlist and removes the song with that title from the song's vector of the playlist
How To Call:
musicManager->deleteSongFromPlaylist("Revolution", "myPlaylist)
Pre-Conditions:
assumes the playlists exists and the specified song was added to the playlist
Post-Conditon:
song deleted from playlist*/
void MusicManager::deleteSongFromPlaylist(std::string songTitle, std::string playlistName) {
	int index;
	Playlist *foundPlaylist = findPlaylist(playlistName, &index);
	if (foundPlaylist != NULL) {
		for (int i=0; i < foundPlaylist->songs.size(); i++) {
			Song *song = foundPlaylist->songs[i];
			if (song->title == songTitle) {
				foundPlaylist->songs.erase(foundPlaylist->songs.begin()+i);
				return;
			}
		}
	}
}
/*Prototype:
Song* musicManager:: findSongInPlaylist(string,string)
Description:
finds the playlist and then finds the song in the song's vector of the playlist and returns a pointer to the song
How to Call
Song* song = musicManager->findSongInPlaylist("Revolution", "myPlaylist")
Pre-Conditions:
assumes playlist exists and song title is in playlist
Post-Conditions:
Returns pointer to song*/
Song * MusicManager::findSongInPlaylist(std::string songTitle, std::string playlistName){
	int index;
	Playlist *foundPlaylist = findPlaylist(playlistName, &index);
	if (foundPlaylist != NULL) {
		for (int i=0; i < foundPlaylist->songs.size(); i++) {
			Song *song = foundPlaylist->songs[i];
			if (song->title == songTitle) {
				return song;
			}
		}
	}
	return NULL;
}
/*Prototype:
void musicManager:: printPlaylist(string)
Description:
prints all songs in specified playlist
How to Call
musicManager->printPlaylist("myPlaylist)
Pre-Conditions:
Assumes playlist exists
Post-Conditions:
none*/
void MusicManager::printPlaylist(std::string playlistName) {
	int index;
	Playlist *foundPlaylist = findPlaylist(playlistName, &index);
	if (foundPlaylist != NULL) {
		for (int i=0; i < foundPlaylist->songs.size(); i++) {
			Song *song = foundPlaylist->songs[i];
			cout<<song->title<<","<<song->artist<<","<<song->genre<<","<<song->popularity<<endl;
		}
	}
}
/*Prototype
Playlist * musicManager:: findPlaylist(string, int*)
Description:
Creates a hash for the playlist name, and find it in the playlist hash table, and returns a pointer to the playlist
How To Call
Playlist* playlist = musicManager->findPlaylist( "myPlaylist", &index)
Pre-Condition:
playlist exits
Post-conditon:
returns a pointer to the playlist*/
Playlist * MusicManager::findPlaylist(std::string name, int *index) {
	int hash = hashSum(name, tableSize);  // get the hash
	*index = hash;
	if (playlists[hash] == NULL) {
		return NULL;
	} else {
		if (playlists[hash]->name == name) {  // song is first in chain
			return playlists[hash];
		} else {
			Playlist *nextPlaylist = playlists[hash]->next;
			while (nextPlaylist != NULL) {            // loop through all playlists in chain
				if (nextPlaylist->name == name) {
					return nextPlaylist;
				} else {
					nextPlaylist = nextPlaylist->next;
				}
			}
			return nextPlaylist;     // playlist not found, return null
		}
	}
}
/*Prototype:
void musicManager:: sortPlaylistByGenre(string)
Description:
finds the given playlist and uses a private sorting algorthim to sort the playlist by genre
How To Call:
musicManager->sortPlaylistByGenre("myPlaylist")
Pre-Condition:
Playlist exists
Post-Condition:
songs in playlist are re-orderd by genre
*/
void MusicManager::sortPlaylistbyGenre(std::string playlistName) {
	int index;
	Playlist *foundPlaylist = findPlaylist(playlistName, &index);
	if ((foundPlaylist != NULL) && (foundPlaylist->songs.size() > 1)) {
		quickSortGenre(&foundPlaylist->songs, 0, foundPlaylist->songs.size()-1);
	}
}
/*Prototype:
void musicManager:: sortPlaylistByPopularity(string)
Description:
finds the given playlist and uses a private sorting algorthim to sort the playlist by genre
How To Call:
musicManager->sortPlaylistByGenre("myPlaylist")
Pre-Condition:
playlist exits
Post-ConditionL:
songs in playlist are re-ordered by genre





*/
void MusicManager::sortPlaylistbyPopularity(std::string playlistName) {
	int index;
	Playlist *foundPlaylist = findPlaylist(playlistName, &index);
	if ((foundPlaylist != NULL) && (foundPlaylist->songs.size() > 1)) {
		quickSortPopularity(&foundPlaylist->songs, 0, foundPlaylist->songs.size()-1);
	}
}

// Add ascii values of all characters in key, then mod by size of table
int MusicManager::hashSum(std::string key, int size) {
	int sum = 0;
	for (int i = 0; i < key.length(); i++) {
	        sum =sum + key[i];  //ascii value of ith character in the string
	}
	sum = sum % size;
	return sum;
}

void MusicManager::quickSortPopularity(std::vector<Song *> *arr, int left, int right) {
     int i = left;
     int j = right;
     Song *tmp;
     Song *pivot = (*arr)[(left + right) / 2];
     while(i <= j){
          while((*arr)[i]->popularity < pivot->popularity)
               i++;
          while((*arr)[j]->popularity > pivot->popularity)
               j--;
          if(i <= j){
               tmp = (*arr)[i];
               (*arr)[i] = (*arr)[j];
               (*arr)[j] = tmp;
               i++;
               j--;
          }
     }
     if (left < j)
          quickSortPopularity(arr, left, j);
     if (i < right)
          quickSortPopularity(arr, i, right);
}

void MusicManager::quickSortGenre(std::vector<Song *> *arr, int left, int right) {
     int i = left;
     int j = right;
     Song *tmp;
     Song *pivot = (*arr)[(left + right) / 2];
     while(i <= j){
          while((*arr)[i]->genre < pivot->genre)
               i++;
          while((*arr)[j]->genre > pivot->genre)
               j--;
          if(i <= j){
               tmp = (*arr)[i];
               (*arr)[i] = (*arr)[j];
               (*arr)[j] = tmp;
               i++;
               j--;
          }
     }
     if (left < j)
          quickSortGenre(arr, left, j);
     if (i < right)
          quickSortGenre(arr, i, right);
}
