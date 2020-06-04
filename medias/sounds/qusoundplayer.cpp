#include "qusoundplayer.h"


QuSoundPlayer::QuSoundPlayer()
{
    playlist = new QMediaPlaylist();
    player = new QMediaPlayer();
    player->setPlaylist(playlist);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
}

QuSoundPlayer::~QuSoundPlayer()
{
    delete playlist;
    delete player;
}

void QuSoundPlayer::play()
{
    player->play();
}

void QuSoundPlayer::pause()
{
    player->pause();
}

void QuSoundPlayer::stop()
{
    player->stop();
}

void QuSoundPlayer::addMusicToPlaylist(QString path)
{
    playlist->addMedia(QUrl(path));
}

void QuSoundPlayer::clearPlaylist()
{
    stop();
    playlist->clear();
}

/**
 * @brief QuSound::setVolume
 * @param volume Value between 0 and 100
 */
void QuSoundPlayer::setVolume(int volume)
{
    player->setVolume(volume);
}

