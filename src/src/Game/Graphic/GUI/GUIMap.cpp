#include <memory>
#include <SDL.h>
#include "Game/__internalConfig/LoggerConfig.h"
#include "GUIMap.h"
#include "../../Gameplay/Data/Settings.h"
#include "DialogMenu.h"
#include "WindowTeam.h"
#include "WindowSettings.h"
#include <GUI/Windows/GUIScrollButtonWindowIG.h>
#include "FPSLabel.h"
#include "../../Gameplay/Fight/SkillsHolderComponent.h"
#include "../../Gameplay/CustomEntityManager.h"

#define TAILLEBLOCFENETRE 32

GUIMap::GUIMap(CustomEntityManager& em, PokemonGameEventDispatcher& ged) :
	ska::GUI(ged),
	ska::Observer<SettingsChangeEvent>(std::bind(&GUIMap::onSettingsChange, this, std::placeholders::_1)),
	ska::Observer<EntityLoadEvent>(std::bind(&GUIMap::onEntityLoad, this, std::placeholders::_1)),
	DialogEventObserver(std::bind(&GUIMap::onDialogEvent, this, std::placeholders::_1)),
	BattleStartObserver(std::bind(&GUIMap::onBattleStart, this, std::placeholders::_1)),
	m_entityManager(em),
	m_ged(ged),
	m_dbgWindow(*this, ged) {
	initButtons();

	auto attachedToCursor = std::unique_ptr<ska::Widget>(std::make_unique<WindowMouseCursor>(this, this, this, ska::Rectangle{0, 0, 64, 96}));
	m_attachedToCursor = static_cast<WindowMouseCursor*>(addTopWidget(attachedToCursor));

	addMasterHandler<ska::HoverEventListener>([this](ska::Widget*, ska::HoverEvent& e) {
		m_attachedToCursor->move(e.getMousePosition() + ska::Point<int>(16, 16));
	});

	m_team = &addFocusableWindow<WindowTeam>("team", m_attachedToCursor, ska::Point<int>(4 * TAILLEBLOCFENETRE, 4 * TAILLEBLOCFENETRE));
	m_team->show(false);

	addFocusableWindow<WindowSettings>("settings", ska::Point<int>(12 * TAILLEBLOCFENETRE, 4 * TAILLEBLOCFENETRE)).show(false);

	m_ged.ska::Observable<BattleEvent>::addObserver(*this);
	m_ged.ska::Observable<SettingsChangeEvent>::addObserver(*this);
	m_ged.ska::Observable<EntityLoadEvent>::addObserver(*this);
	m_ged.ska::Observable<DialogEvent>::addObserver(*this);
}

void GUIMap::refresh(unsigned int ellapsedTime) {
	GUI::refresh(ellapsedTime);
	m_dbgWindow.refresh(ellapsedTime);
}

void GUIMap::bind(Settings& sets) {
	auto wsettings = reinterpret_cast<WindowSettings*>(getWindow("settings"));
	wsettings->bind(sets);
}

void GUIMap::initButtons() {
	ska::Rectangle buf;
    buf.w = (TAILLEBLOCFENETRE)* 2;
    buf.h = (TAILLEBLOCFENETRE)* 4;
    buf.x = 0;
    buf.y = 0;

	//TODO widget dans classe � part
	m_wAction = &addWindow<ska::TimeScrollableWindowIG<>>("actions", ska::Rectangle{ 0, 0, 13 * TAILLEBLOCFENETRE, 2 * TAILLEBLOCFENETRE });
	m_wAction->setPriority(0);
	resort();

    auto& wAction = static_cast<ska::TimeScrollableWindowIG<>&>(*m_wAction);
    wAction.move(ska::Point<int>(getMaxWidth() - 13 * TAILLEBLOCFENETRE, getMaxHeight() - wAction.getBox().h / 2));

    auto scrollButtonLambda = [this](ska::Widget* tthis, ska::HoverEvent& e) {
        auto target = static_cast<ska::GUIScrollButtonWindowIG*>(tthis);
        if (e.getState() == ska::MOUSE_OUT) {
            target->scrollRewind();
        } else if (e.getState() == ska::MOUSE_ENTER) {
            target->scrollTo(ska::Point<int>(target->getRelativePosition().x, -target->getBox().w / 3), 5);
        }

    };

    auto& firstButton = wAction.addWidget<ska::GUIScrollButtonWindowIG>(buf);
	auto& bs = firstButton.addWidget<ska::ButtonSprite>(ska::Point<int>(), "", 102, [&](ska::Widget*, const ska::ClickEvent& e) {
        if (e.getState() == ska::MOUSE_CLICK) {
            auto widget = getWindow("team");
            widget->show(!widget->isVisible());
        }
    });
    bs.setName("POKEBALL BUTTON");
    firstButton.setName("POKEBALL MENU");

    firstButton.addHandler<ska::HoverEventListener>(scrollButtonLambda);
    wAction.setName("ACTIONS");

	static constexpr auto OFFSET_BETWEEN_BUTTONS = 2.5 * TAILLEBLOCFENETRE;

    buf.x += OFFSET_BETWEEN_BUTTONS;
    auto& secondButton = wAction.addWidget<ska::GUIScrollButtonWindowIG>(buf);
    secondButton.addHandler<ska::HoverEventListener>(scrollButtonLambda);

	buf.x += OFFSET_BETWEEN_BUTTONS;
    auto& thirdButton = wAction.addWidget<ska::GUIScrollButtonWindowIG>(buf);
    thirdButton.addHandler<ska::HoverEventListener>(scrollButtonLambda);

	buf.x += OFFSET_BETWEEN_BUTTONS;
    auto& fourthButton = wAction.addWidget<ska::GUIScrollButtonWindowIG>(buf);
    fourthButton.addHandler<ska::HoverEventListener>(scrollButtonLambda);

	buf.x += OFFSET_BETWEEN_BUTTONS;
    auto& fifthButton = wAction.addWidget<ska::GUIScrollButtonWindowIG>(buf);
    fifthButton.addHandler<ska::HoverEventListener>(scrollButtonLambda);
	fifthButton.addWidget<ska::ButtonSprite>(ska::Point<int>(1, 1), "", 104, [&](ska::Widget*, const ska::ClickEvent& e) {
        if (e.getState() == ska::MOUSE_CLICK) {
            auto widget = getWindow("settings");
            widget->show(!widget->isVisible());
        }
    });
}

bool GUIMap::onDialogEvent(DialogEvent& de) {
    if(getWindow(de.name) == nullptr) {
        ska::Rectangle absoluteRect;
        absoluteRect.w = (de.box.w < 0) ? getMaxWidth() - 1 : de.box.w;
        absoluteRect.h = (de.box.h < 0) ? getMaxHeight() - 1 : de.box.h;
		const auto maxLimitY = de.box.y > static_cast<int>(getMaxHeight());
		const auto maxLimitX = de.box.x > static_cast<int>(getMaxHeight());
        absoluteRect.y = (de.box.y < 0) ? getMaxHeight() - absoluteRect.h - 1 : (maxLimitY ? (getMaxHeight() - absoluteRect.h) : de.box.y);
        absoluteRect.x = (de.box.x < 0) ? getMaxWidth() - absoluteRect.w - 1 : (maxLimitX ? (getMaxWidth() - absoluteRect.w) : de.box.x);

		auto startRect = absoluteRect;
		startRect.y += startRect.h - 1;
        auto& dialogWindow = addFocusableWindow<DialogMenu>(de.name, de.message, de.name, startRect, 12);
		
		m_dialogScript = de.callbackActive ? de.callback : std::optional<ska::ScriptSleepComponent>{};

        if(de.scroll) {
            dialogWindow.scrollTo(ska::Point<int>(absoluteRect.x, absoluteRect.y), 8)
            .then([this](ska::TimeScrollableWindowIG<ska::KeyEventListener>& caller) {
                auto& sdialogWindow = static_cast<DialogMenu&>(caller);
                sdialogWindow.addHandler<ska::KeyEventListener>([this] (ska::Widget* tthis, ska::KeyEvent& ke) {
                    if(ke.getScanCode() == SDL_SCANCODE_RETURN) {
                        auto target = static_cast<DialogMenu*>(tthis);

                        target->scrollTo(ska::Point<int>(target->getRelativePosition().x, getMaxHeight() + 1), 8)
                        .then([this](ska::TimeScrollableWindowIG<ska::KeyEventListener>& caller) {
                              ska::GUIEvent ge(ska::GUIEventType::REMOVE_WINDOW);
                              ge.windowName = static_cast<DialogMenu&>(caller).getName();
                              m_ged.ska::Observable<ska::GUIEvent>::notifyObservers(ge);

							  if (m_dialogScript.has_value()) {
								  /* triggers callback */
								  const auto scriptEntity = m_entityManager.createEntity();
								  auto events = std::vector<ska::ScriptEventType>();
								  events.push_back(ska::ScriptEventType::ScriptCreate);
								  auto se = ska::ScriptEvent{ std::move(events), std::move(*m_dialogScript), scriptEntity, {}, {}, {}, {} };
								  m_ged.Observable<ska::ScriptEvent>::notifyObservers(se);
							  }
                        });
                    }
                });
            });
        }
    }
    return true;
}

bool GUIMap::onScreenResized(unsigned int width, unsigned int height) {
	auto& wAction = static_cast<ska::TimeScrollableWindowIG<>&>(*m_wAction);
	wAction.move(ska::Point<int>(width - 13 * TAILLEBLOCFENETRE, height - wAction.getBox().h / 2));

	return true;
}

bool GUIMap::onSettingsChange(SettingsChangeEvent& sce) {
	auto wsettings = reinterpret_cast<WindowSettings*>(getWindow("settings"));

	if((static_cast<int>(sce.eventType) & static_cast<int>(SettingsChangeEventType::MUSIC_VOLUME)) == static_cast<int>(SettingsChangeEventType::MUSIC_VOLUME)) {
		wsettings->setMusicVolume(sce.settings.getSoundVolume()/100);
	}

	if ((static_cast<int>(sce.eventType) & static_cast<int>(SettingsChangeEventType::FOG)) == static_cast<int>(SettingsChangeEventType::FOG)) {
		wsettings->setFog(sce.settings.getFogActive());
	}

	if ((static_cast<int>(sce.eventType) & static_cast<int>(SettingsChangeEventType::WEATHER)) == static_cast<int>(SettingsChangeEventType::WEATHER)) {
		wsettings->setWeather(sce.settings.getWeatherActive());
	}

	return true;
}

bool GUIMap::onEntityLoad(EntityLoadEvent& ele) {
	/* add a Pokemon to the GUI team (from the event) */
	auto& wTeam = static_cast<WindowTeam&>(*getWindow("team"));

	auto spd1 = std::make_unique<SlotPokemonData>();
	/* TODO data from Pkmn Database */
	spd1->id = ele.id;
	spd1->hp = ska::StringUtils::uintToStr(ele.currentHp);
	spd1->name = ele.description->name;
	spd1->level = ska::StringUtils::intToStr(ele.stats->getLevel());
	spd1->type1 = ele.description->type1;
	spd1->type2 = ele.description->type2;

	wTeam.insertPokemon(nullptr, move(spd1));

	return true;
}

bool GUIMap::onBattleStart(BattleEvent& be){
	if(be.getEventType() == BATTLE_START) {
		auto& em = be.getEntityManager();
		const auto& sh = em.getComponent<SkillsHolderComponent>(be.getBattler());
		m_skillBar = &addWindow<SkillsBar>("skillsBar", sh.skills, getMaxWidth(), getMaxHeight());
	} else {
		removeWindow("skillsBar");
		m_skillBar = nullptr;
	}
	return true;
}

GUIMap::~GUIMap() {
	m_ged.ska::Observable<DialogEvent>::removeObserver(*this);
	m_ged.ska::Observable<SettingsChangeEvent>::removeObserver(*this);
	m_ged.ska::Observable<EntityLoadEvent>::removeObserver(*this);
	m_ged.ska::Observable<BattleEvent>::removeObserver(*this);
}

