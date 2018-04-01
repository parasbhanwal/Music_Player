#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->songlabel->setText(" CREATE SONG LIST FRIST ");
    player->setVolume(volume);

    connect(timer , SIGNAL(timeout()) , this , SLOT(songstatus()));
    connect(timer , SIGNAL(timeout()) , this , SLOT(playtimer()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_nextsong_clicked()
{
    if( ui->listWidget->count() != 0 )
    {

        if( repeatone == true )
            loadtrack( current_index() );
        else
        {
            int index =  current_index() + 1;
            if( index < ui->listWidget->count() )
                loadtrack( index );
            else
            {
                if( repeatall == true )
                    loadtrack( 0 );
                else
                {
                    ui->listWidget->setCurrentRow(0);
                    ui->songlabel->setText(playlist.Song.at(0));
                    loadtrack( 0 );
                    ui->play_pause->setChecked(true);
                }
            }
            if( ui->play_pause->isChecked() == true )
                player->pause();
        }
    }
}

void Widget::on_previoussong_clicked()
{
    if( ui->listWidget->count() != 0 )
    {
        ui->listWidget->setCurrentRow( current_index() - 1 );
        loadtrack( current_index() );

        if( ui->play_pause->isChecked() == true )
        player->pause();
    }
}

void Widget::on_play_pause_clicked()
{
    if( ui->listWidget->count() != 0 )
    {
        if( player->state() == QMediaPlayer::PausedState )
         {
            player->play();
            ui->play_pause->setText("I I");
            ui->play_pause->setStyleSheet("border:2px solid black;color:black;border-radius : 25px;background-color: rgb(255, 255, 255);");
            ui->play_pause->setToolTip("PAUSE");
        }
        else
         {
            player->pause();
            ui->play_pause->setText("I >");
            ui->play_pause->setStyleSheet("border:2px solid red;color:red;border-radius : 25px;background-color: rgb(255, 255, 255);");
            ui->play_pause->setToolTip("PLAY");
        }
    }
    else
        ui->play_pause->setChecked(false);
}

void Widget::on_removesong_clicked()
{
    if( ui->listWidget->count() != 0 )
    {
        int index = current_index();
        playlist.remove( current_index() );
        ui->listWidget->clear();
        ui->listWidget->addItems(playlist.tracklist());

        if( ui->listWidget->count() == 0 )
        {
            ui->songlabel->setText(" CREATE SONG LIST FRIST ");
            player->pause();
        }
        else
            loadtrack( index );
    }
}

void Widget::on_addsong_clicked()
{
    int count = ui->listWidget->currentRow();
    QStringList Songlist = QFileDialog::getOpenFileNames( this , tr("****** Select Music Files ******") );
    if(!Songlist.empty())
    {

        playlist.add( Songlist );
        ui->listWidget->clear();
        ui->listWidget->addItems( playlist.tracklist() );
        if( count == -1 )
            loadtrack( current_index() );
        else
            ui->listWidget->setCurrentRow(count);
    }
}

void Widget::on_listWidget_doubleClicked()
{
    loadtrack( current_index() );
}

void Widget::loadtrack( int index )
{
    if( index == -1 )
        index = 0;
    ui->listWidget->setCurrentRow( index );
    player->setMedia( QUrl::fromLocalFile( playlist.Song_Add.at(index) ) );
    ui->songlabel->setText( playlist.Song.at(index) );
    ui->play_pause->setText("I I");
    ui->play_pause->setStyleSheet("border:2px solid black;color:black;border-radius : 25px;background-color: rgb(255, 255, 255);");
    ui->play_pause->setToolTip("PAUSE");
    player->play();
    ui->songduration->setText(calculate_song_length( player->duration() / 1000 ));
    timer->start();

}

void Widget::on_repeatone_clicked()
{
    ++repeatone;
    repeatall=false;
}

void Widget::on_repeatall_clicked()
{
    ++repeatall;
    repeatone=false;
}

void Widget::songstatus()
{

    ui->SongSlider->setValue((double)(player->position() * 100 / player->duration() ));
    if( player->state() == QMediaPlayer::StoppedState )
        on_nextsong_clicked();

}

QString Widget::calculate_song_length(long long int length)
{
    QString qstr;
    long long int min = length/60;
    qstr.push_back(QString::number( min ));
    qstr.push_back(" min : ");
    length %= 60;
    qstr.push_back(QString::number( length ));
    qstr.push_back(" sec");
    return qstr;
}

int Widget::current_index()
{
    return ui->listWidget->currentRow();
}

void Widget::playtimer()
{
    ui->songplayed->setText( calculate_song_length(player->position()/1000));
}

void Widget::on_SongSlider_sliderMoved( int position )
{
    player->setPosition( (double)position *1000/player->duration() );
}
void Widget::on_volume_clicked()
{
    if( mute == false )
    {
        mute = true;
        ui->volume->setIcon(QIcon(":/icons/icons/mute.png"));
        player->setVolume(0);
    }
    else
    {
        mute = false ;
        ui->volume->setIcon(QIcon(":/icons/icons/volume.png"));
        player->setVolume(100);
    }
}

void Widget::on_volumelevel_sliderMoved(int position)
{

}
