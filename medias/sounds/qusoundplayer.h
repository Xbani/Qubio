#ifndef QUSOUNDPLAYER_H
#define QUSOUNDPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

class QuSoundPlayer
{
public:
    QuSoundPlayer();
    ~QuSoundPlayer();
    void play();
    void pause();
    void stop();
    void addMusicToPlaylist(QString path);
    void clearPlaylist();
    void setVolume(int volume);

private:
    QMediaPlaylist * playlist;
    QMediaPlayer * player;

public:
    const QString SOUND_MAIN_THEME    = "qrc:/resources/sounds/mainTheme.mp3";
    const QString SOUND_WAINTING      = "qrc:/resources/sounds/waiting.mp3";
};

#endif // QUSOUNDPLAYER_H
