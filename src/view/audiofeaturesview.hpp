#pragma once

#include "../util/utils.hpp"
#include "spotify/spotify.hpp"

#include <QAbstractItemView>
#include <QDockWidget>
#include <QHeaderView>
#include <QTreeWidget>

class AudioFeaturesView: public QTreeWidget
{
Q_OBJECT

public:
	AudioFeaturesView(spt::Spotify &spotify, const QString &trackId, QWidget *parent);
};