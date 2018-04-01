#ifndef WIDGET_H
#define WIDGET_H

#include "playlist.h"
#include <QWidget>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>
namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void playtimer();

    void songstatus();

    void on_addsong_clicked();

    void on_removesong_clicked();

    void on_nextsong_clicked();

    void on_previoussong_clicked();

    void on_play_pause_clicked();

    void on_listWidget_doubleClicked();

    void loadtrack( int index );

    void on_repeatone_clicked();

    void on_repeatall_clicked();

    void on_SongSlider_sliderMoved(int position);

    void on_volume_clicked();

    void on_volumelevel_sliderMoved(int position);

private:

    QString calculate_song_length( long long int length );

    int current_index();

    bool repeatone = false ;

    bool repeatall = false;

    bool mute = false ;

    int volume = 100;

    Playlist playlist;

    Ui::Widget *ui;

    QTimer *timer = new QTimer(this);

    QMediaPlayer *player = new QMediaPlayer();
};

#endif // WIDGET_HS
