#include "ButtonQuit.h"

ska::ButtonQuit::ButtonQuit(MouseObservable& guiObservable, Widget& parent, ska::Point<int> relativePos, const std::string& placeHolderStyleName) :
Button(guiObservable, parent, relativePos, placeHolderStyleName, [&](const ska::ClickEvent& e){
	parent.show(false);
}) {
}
