#include "settingspage/shortcuts.hpp"
#include "settingspage/base.hpp"
#include "util/widget.hpp"

#include <QLabel>
#include <QLineEdit>

SettingsPage::Shortcuts::Shortcuts(lib::settings &settings, QWidget *parent)
    : SettingsPage::Base(settings, parent)
{
    addTab(shortcuts(), "Shortcuts");
}

auto SettingsPage::Shortcuts::shortcuts() -> QWidget *
{
    auto *layout = new QVBoxLayout();

    auto *ppLayout = new QHBoxLayout();
    auto *plShortCut = new QLabel(this);
    plShortCut->setText(tr("Play/Pause: "));
    ppLayout->addWidget(plShortCut);

    ppLayout->addStretch();

    auto *scInput = new QLineEdit(this);
    scInput->setPlaceholderText(tr("Press the key to set a shortcut."));
    scInput->setMinimumWidth(300);
    scInput->setReadOnly(true);
    ppLayout->addWidget(scInput);

    layout->addLayout(ppLayout);
    layout->addStretch();

    return Widget::layoutToWidget(layout, this);
}

auto SettingsPage::Shortcuts::icon() -> QIcon
{
    return QIcon("");
}

auto SettingsPage::Shortcuts::title() -> QString
{
    return tr("Shortcuts");
}

auto SettingsPage::Shortcuts::save() -> bool
{
    return true;
}


