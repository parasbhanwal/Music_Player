#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <QVector>

class Playlist
{
    public:

        void add( QStringList songs_add );

        void remove( int index );

        QVector<QString> Song;

        QVector<QString> Song_Add;

        QStringList tracklist();

        QString getnamefromlocation( QString str );


};

#endif // PLAYLIST_H
