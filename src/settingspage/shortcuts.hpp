#pragma once

#include "settingspage/base.hpp"


namespace SettingsPage
{
	class Shortcuts: public Base
	{
	public:
		Shortcuts(lib::settings &settings, QWidget *parent);

		auto icon() -> QIcon override;
		auto title() -> QString override;
		auto save() -> bool override;

	private:

		auto shortcuts() -> QWidget *;
	};
}
