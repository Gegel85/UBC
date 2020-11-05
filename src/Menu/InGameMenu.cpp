//
// Created by andgel on 15/10/2020.
//

#include "InGameMenu.hpp"
#include "../Resources/State.hpp"

#define INCREMENT_VAR(var)                                      \
        if (                                                    \
        	std::find(                                      \
        		this->_state.flags.begin(),             \
        		this->_state.flags.end(),               \
        		"no_"#var                               \
		) == this->_state.flags.end()                   \
	)                                                       \
                this->_state.var += this->_state.var##Passive;  \
	this->_state.flags.erase(std::remove(                   \
		this->_state.flags.begin(),                     \
		this->_state.flags.end(),                       \
		"no_"#var), this->_state.flags.end()            \
	)

namespace UntilBeingCrowned
{
	InGameMenu::InGameMenu(MenuMgr &mgr, tgui::Gui &gui, Resources &res, QuestMgr &dialogs, GameState &state) :
		_res(res),
		_gui(gui),
		_mgr(mgr),
		_questsMgr(dialogs),
		_state(state)
	{
	}

	InGameMenu::~InGameMenu()
	{
		this->_questsMgr.onClick(nullptr);
	}

	void InGameMenu::switched(bool isActive)
	{
		if (!isActive) {
			this->_gui.removeAllWidgets();
			this->_questsMgr.onClick(nullptr);
			return;
		}
		this->_gui.loadWidgetsFromFile("gui/igmenu.gui");
		this->_goldsLabel = this->_gui.get<tgui::Label>("Gold");
		this->_armyLabel = this->_gui.get<tgui::Label>("Army");
		this->_foodLabel = this->_gui.get<tgui::Label>("Food");
		this->_passiveGoldsLabel = this->_gui.get<tgui::Label>("PassiveGold");
		this->_passiveArmyLabel = this->_gui.get<tgui::Label>("PassiveArmy");
		this->_passiveFoodLabel = this->_gui.get<tgui::Label>("PassiveFood");
		this->_nobilityHappinessLabel = this->_gui.get<tgui::Label>("NobilityHappiness");
		this->_peasantsHappinessLabel = this->_gui.get<tgui::Label>("PeasantsHappiness");
		this->_tradersHappinessLabel = this->_gui.get<tgui::Label>("TradersHappiness");
		this->_questsMgr.showDialog(0, this->_gui);
		this->_hookHandlers();
	}

	void InGameMenu::render()
	{
		auto newQuestsList = this->_gui.get<tgui::Button>("NewQuests");

		newQuestsList->setEnabled(!this->_questsMgr.getNewQuests().empty());
		this->_goldsLabel->setText(std::to_string(this->_state.gold));
		this->_armyLabel->setText(std::to_string(this->_state.army));
		this->_foodLabel->setText(std::to_string(this->_state.food));
		this->_passiveGoldsLabel->setText("+" + std::to_string(this->_state.goldPassive));
		this->_passiveArmyLabel->setText("+" + std::to_string(this->_state.armyPassive));
		this->_passiveFoodLabel->setText("+" + std::to_string(this->_state.foodPassive));
		this->_nobilityHappinessLabel->setText(std::to_string(this->_state.nobilityHappiness));
		this->_peasantsHappinessLabel->setText(std::to_string(this->_state.peasantsHappiness));
		this->_tradersHappinessLabel->setText(std::to_string(this->_state.tradersHappiness));
		this->_res.screen.draw(
			this->_res.textures["igproto"],
			{0, 0},
			this->_res.screen.getSize()
		);
	}

	void InGameMenu::handleEvent(const Input::Event &)
	{

	}

	void InGameMenu::_showQuestList(const std::vector<QuestMgr::Quest> &quests, const std::string &name)
	{
		auto label = tgui::Label::create(name);
		auto picture = tgui::Panel::create({600, 700});
		auto panelBack = tgui::Panel::create({"100%", "100%"});
		std::weak_ptr<tgui::Panel> panelBackPtr = panelBack;
		auto panel = tgui::ScrollablePanel::create({450, 550});
		auto close = [panelBackPtr, label, picture, this]{
			this->_gui.remove(panelBackPtr.lock());
			this->_gui.remove(picture);
			this->_gui.remove(label);
		};
		auto closeButton = tgui::Button::create("OK");

		label->getRenderer()->setFont("assets/kenpixel.ttf");
		label->setTextSize(25);
		panel->getRenderer()->setBackgroundColor({0, 0, 0, 0});
		panelBack->getRenderer()->setBackgroundColor({0, 0, 0, 175});
		picture->getRenderer()->setTextureBackground(this->_res.textures["list_bg"]);
		closeButton->setPosition("&.w - w - 10", "&.h - h - 10");
		picture->setPosition("&.w / 2 - w / 2", "&.h / 2 - h / 2");
		label->setPosition("&.w / 2 - w / 2", 45);
		panel->setPosition("&.w / 2 - w / 2", "&.h / 2 - h / 2");
		picture->add(closeButton);
		closeButton->getRenderer()->setFont("assets/kenpixel.ttf");
		closeButton->onClick.connect(close);
		panelBack->onClick.connect(close);
		picture->add(panel);
		picture->add(label);
		this->_gui.add(panelBack);
		this->_gui.add(picture, "Panel");
		for (size_t i = 0; i < quests.size(); i++) {
			const auto &quest = quests[i];
			auto button = tgui::Button::create(quest.title);

			button->getRenderer()->setFont("assets/kenpixel.ttf");
			button->setPosition(10, i * 30 + 10);
			button->setSize("&.w - 20", 20);
			button->onClick.connect([this, quest, close]{
				close();
				this->_questsMgr.showDialog(quest.getId(), this->_gui);
			});
			panel->add(button);
		}
	}

	void InGameMenu::_hookHandlers()
	{
		auto newQuestsList = this->_gui.get<tgui::Button>("NewQuests");
		auto unlockedQuestsList = this->_gui.get<tgui::Button>("Quests");
		auto nextWeek = this->_gui.get<tgui::Button>("Next");

		nextWeek->onClick.connect([this]{
			this->_nextWeek();
		});
		newQuestsList->onClick.connect([this]{
			this->_showQuestList(this->_questsMgr.getNewQuests(), "New quests");
		});
		unlockedQuestsList->onClick.connect([this]{
			this->_showQuestList(this->_questsMgr.getUnlockedQuests(), "Unlocked Quests");
		});
	}

	void InGameMenu::_nextWeek()
	{
		INCREMENT_VAR(gold);
		INCREMENT_VAR(army);
		INCREMENT_VAR(food);
		this->_state.week++;
		this->_questsMgr.nextWeek();
	}
}
