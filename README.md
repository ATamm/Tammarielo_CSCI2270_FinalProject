# Tammarielo_CSCI2270_FinalProject

Project Summary
The program uses 2 hash tables to manage a music inventory for a radio station and several playlists for Dj's or requests.
Movies contain a title and an artist, as well as a genre definition, and a popularity number based on the number of plays(1-30). The program reads in a pre-defined list of titles which make up the inventory. Although additional titles can be added as the music library is expanded. The title is the key to the hash-table. Users can print the inventory, or search for specific titles within the inventory, and can also create a playlist and add or delete titles from the playlist as well as delete entire playlists. The program can also sort individual playlists by Genre, or by popularity by song.




How to run.
To run this program, make sure that the SomeSongs.txt file is included in the same folder as the .cpp files and the .h files. compile using g++ and include the songs.txt in the ./a.out command line.This program does not take any command line arguments. The song library will be there, from there you can print the library, add songs to a playlist, delete songs and individual playlists. Sort playlists, find playlists etc. The menu will provide the range of functions you can call.





Dependencies
The only dependecies needed is the SomeSongs.txt which is provided, everything else is provided. Makes sure the .h is there!





System requirements 
The program is designed to run on Linux.



Group Members 
No other group members

Contributors
no other contributers

Open Issues
When deleting a song from inventory, if that song is inside of a created playlist the program will seg fault.
