#include "playlist.h"

void Playlist::add( QStringList songs_add )
{
    for( int i=0 ; i<songs_add.size() ; ++i )
        {
            Song_Add.push_back(songs_add.at(i));
            Song.push_back(getnamefromlocation(songs_add.at(i)));
        }
}

void Playlist::remove( int index )
{
    Song.erase( Song.begin() + index);
    Song.shrink_to_fit();
    Song_Add.erase(  Song_Add.begin() + index );
    Song_Add.shrink_to_fit();
}

QString Playlist::getnamefromlocation( QString str )
{
    QString song_name;
    for( int i=str.size()-1; str[i]!='/'; --i )
        song_name.push_front( str.at(i) );

    return song_name;
}
QStringList Playlist::tracklist()
{
    QStringList Slist;
    for( int i=0; i<Song.size(); ++i )
       Slist.push_back( Song.at(i) );

    return Slist;
}
