/*
 * #include "qusound.h"


QuSound::QuSound()
{
    playlist = new QMediaPlaylist();
    player = new QMediaPlayer();
    player->setPlaylist(playlist);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
}

QuSound::~QuSound()
{
    delete playlist;
    delete player;
}

void QuSound::play()
{
    player->play();
}

void QuSound::pause()
{
    player->pause();
}

void QuSound::stop()
{
    player->stop();
}

void QuSound::addMusicToPlaylist(QString path)
{
    playlist->addMedia(QUrl(path));
}

void QuSound::clearPlaylist()
{
    stop();
    playlist->clear();
}

/**
 * @brief QuSound::setVolume
 * @param volume Value between 0 and 100
 */
/*void QuSound::setVolume(int volume)
{
    player->setVolume(volume);
}
*/
