#include "developermenu.hpp"

DeveloperMenu::DeveloperMenu(lib::settings &settings, lib::spt::api &spotify,
	lib::cache &cache, QWidget *parent)
	: spotify(spotify),
	settings(settings),
	cache(cache),
	QMenu("Developer", parent)
{
	setIcon(Icon::get("folder-txt"));

	addMenuItem(this, "Test API requests", [this]()
	{
		auto *mainWindow = MainWindow::find(parentWidget());
		mainWindow->addSidePanelTab(new DebugView(this->settings, mainWindow), "API request");
	});

	addMenuItem(this, "Reset size", [this]()
	{
		MainWindow::find(parentWidget())->resize(MainWindow::defaultSize());
	});

	addMenuItem(this, "Refresh access token", [this]()
	{
		try
		{
			this->spotify.refresh();
			QMessageBox::information(this, "Success",
				QString::fromStdString(lib::fmt::format("Successfully refreshed access token:\n{}",
					this->settings.account.refresh_token)));
		}
		catch (const std::exception &e)
		{
			QMessageBox::critical(this, "Error",
				QString("Refresh failed: %1").arg(e.what()));
		}
	});

	addMenu(infoMenu());
	addMenu(dialogMenu());
}

void DeveloperMenu::addMenuItem(QMenu *menu, const QString &text,
	const std::function<void()> &triggered)
{
	auto *action = menu->addAction(text);
	QAction::connect(action, &QAction::triggered, [triggered](bool /*checked*/)
	{
		triggered();
	});
}

auto DeveloperMenu::dialogMenu() -> QMenu *
{
	auto *menu = new QMenu("Dialogs", this);
	auto *mainWindow = MainWindow::find(parentWidget());

	std::vector<QDialog *> dialogs = {
		new DeviceSelectDialog({}, mainWindow),
		new OpenLinkDialog("/", LinkType::Path, mainWindow),
		new SetupDialog(settings, mainWindow),
		new TracksCacheDialog(cache, mainWindow),
		new WhatsNewDialog(APP_VERSION, settings, mainWindow),
	};

	for (auto *dialog : dialogs)
	{
		addMenuItem(menu, dialog->metaObject()->className(), [dialog]()
		{
			dialog->open();
		});
	}

	return menu;
}

auto DeveloperMenu::infoMenu() -> QMenu *
{
	auto *menu = new QMenu("Current", this);
	auto *mainWindow = MainWindow::find(parentWidget());

	addMenuItem(menu, "Playback", [mainWindow]()
	{
		nlohmann::json json = mainWindow->currentPlayback();
		QMessageBox::information(mainWindow, "Playback",
			QString::fromStdString(json.dump(4)));
	});

	addMenuItem(menu, "Context", [mainWindow]()
	{
		QMessageBox::information(mainWindow, "Context",
			QString::fromStdString(mainWindow->getSptContext()));
	});

	return menu;
}
