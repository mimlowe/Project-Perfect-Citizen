//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
#define resourcePath() std::string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

///////////////////////////////////////////////////////////

#include "../Engine/debug.h"
#include "FloppyInputComponent.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "../Engine/Entity.h"

#include "../Engine/FreeFunctionObserver.h"

using namespace ppc;

const std::string FLOPPY_DEBUG_CODE = "fl";

std::vector<std::vector<FloppyExpression>> FloppyInputComponent::floppyDictionary;
bool FloppyInputComponent::initialized = false;

std::map<std::string, unsigned int> FloppyInputComponent::Floppy_Sequence_Names;

FloppyInputComponent::FloppyInputComponent() {

    if (!initialized) {
        initializeFloppyDict();
    }
}

FloppyInputComponent::~FloppyInputComponent() {

}

const std::array<std::string, 2> FLOPPY_SOURCES{
	"PipelineTutorial.txt",
	"DesktopTutorial.txt"
};

const std::map<std::string, int> FLOPPY_EMOTION_MAP{
	{"Default"   , 0},
    {"Angry"     , 1},
    {"Surprised" , 2},
    {"Peek"      , 3},
};



void ppc::FloppyInputComponent::initializeFloppyDict() {
	for (const auto& filename: FLOPPY_SOURCES) {
		std::ifstream myfile(resourcePath() + filename);
		if (myfile.is_open()) {
			std::string line;
			std::string label;
			std::vector<FloppyExpression> sequence;
			while (std::getline(myfile, line)) {
				if (line.substr(0, 1).compare("-") == 0) {
					if (sequence.empty()) {
						label = line.substr(1);
						continue;
					}

					floppyDictionary.push_back(sequence);
					Floppy_Sequence_Names.insert(std::make_pair(label, floppyDictionary.size() - 1));
					sequence.clear();
					label = line.substr(1);
				}
				else {
					std::string emotion = line.substr(0, line.find_first_of(':'));
					line = line.substr(line.find_first_of(':') + 2);
					FloppyExpression newExpr;
					if (line.substr(0, 1).compare("T") == 0) newExpr.createEnabled = true;
					else newExpr.createEnabled = false;

					if (FLOPPY_EMOTION_MAP.find(emotion) != FLOPPY_EMOTION_MAP.end()) {
						newExpr.emotion = FLOPPY_EMOTION_MAP.at(emotion);
					}
					else newExpr.emotion = FLOPPY_EMOTION_MAP.at("Default");
					
					newExpr.text = line.substr(3);
					sequence.push_back(newExpr);

				}
			}
			floppyDictionary.push_back(sequence);
			Floppy_Sequence_Names.insert(std::make_pair(label, floppyDictionary.size() - 1));
		}
		else {
			DEBUGF(FLOPPY_DEBUG_CODE, filename + " could not be opened");
		}
		myfile.close();
	}
    initialized = true;

	//std::vector<std::pair<std::string, unsigned int>> sequence1;
	//std::pair<std::string, unsigned int> sequence1frame1;
	//std::pair<std::string, unsigned int> sequence1frame2;

	//sequence1frame1 = std::make_pair("BAD COP NADER", 0);
	//sequence1frame2 = std::make_pair("MACK DADDY", 1);
	//sequence1.push_back(sequence1frame1);
	//sequence1.push_back(sequence1frame2);

	//floppyDictionary.push_back(sequence1);
}

unsigned int ppc::FloppyInputComponent::getFrame() { return frame; }

unsigned int ppc::FloppyInputComponent::getSequence() { return sequence; }

void ppc::FloppyInputComponent::setFrame(unsigned int f) { 
    frame = f; 
    Event ev;

    if (floppyDictionary.at(sequence).size() <= frame) {
        frame = -1;
        ev.type = Event::AbleType;
        ev.able.enable = false;
        getEntity()->broadcastMessage(ev);


        ev.type = ppc::Event::FloppyType;
        ev.floppy.sequence = sequence;
        ev.floppy.frame = -1;
        onSequenceEnd().sendEvent(ev);
    }

    ev.type = ppc::Event::FloppyType;
    ev.floppy.sequence = sequence;
    ev.floppy.frame = frame;
    getEntity()->broadcastMessage(ev);

    bool buttonEnabled = floppyDictionary.at(sequence).at(frame).createEnabled;
    setFloppyButton(buttonEnabled);
}

void ppc::FloppyInputComponent::setSequence(unsigned int s, unsigned int f) { 
    if (s < floppyDictionary.size()) {
        sequence = s;
    } else {
        sequence = -1;
    }
    setFrame(f);
}

void ppc::FloppyInputComponent::advanceFrame() { 
	setFrame(frame + 1);
}

void ppc::FloppyInputComponent::regressFrame() { 
    setFrame(frame - 1);
}

void ppc::FloppyInputComponent::advanceSequence() { 
    setSequence(sequence + 1);
}

void ppc::FloppyInputComponent::regressSequence() { 
    setSequence(sequence - 1);
}

bool ppc::FloppyInputComponent::registerInput(Event ev) { return true; }

void ppc::FloppyInputComponent::setFloppyButtonRenderCmpt(buttonRenderComponent * brc)
{
	floppyBtnRndr = brc;
}

void ppc::FloppyInputComponent::setFloppyButtonInputCmpt(mousePressButton * mpb)
{
	floppyBtnInpt = mpb;
}

void ppc::FloppyInputComponent::setFloppyButton(bool able)
{
	ppc::Event ppcEv;
	ppcEv.type = ppc::Event::EventTypes::AbleType;
	ppcEv.able.enable = able;
	floppyBtnInpt->recieveMessage(ppcEv);
	floppyBtnRndr->recieveMessage(ppcEv);
}

bool ppc::summonFloppyDialog(FloppyInputComponent* ptr, ppc::Event ev) {
    bool wasSummoned = false;
    unsigned int frame = 0, sequence = 0;

	switch (ev.type) {
    case ppc::Event::FloppyType:

        //If we just ended a frame
        if (ev.floppy.frame == -1) {
            //If we just ended the Welcome
            if (ev.floppy.sequence != 2) {
                wasSummoned = true;
                ev.floppy.frame = 0;
                ++ev.floppy.sequence;
            }
        } else {
            wasSummoned = true;
        }

        break;
    case Event::OpenType:
        //If we are opening the pipeline:
        if (ev.open.winType == ev.open.Pipeline) {
            wasSummoned = true;
            ev.type = Event::FloppyType;
            ev.floppy.sequence = FloppyInputComponent::Floppy_Sequence_Names.at("Welcome");
            ev.floppy.frame = 0;
        }
        break;
	}

    if (wasSummoned) {
        /* Also let the textbox and button that
        they should spawn */
        ptr->setSequence(ev.floppy.sequence, ev.floppy.frame);
        ptr->getEntity()->broadcastMessage(ev);

        ev.type = ppc::Event::AbleType;
        ev.able.enable = true;
        ptr->getEntity()->broadcastMessage(ev);
    }

	return true;
}


bool ppc::incrementFloppyDialog(FloppyInputComponent* ptr, ppc::Event ev) {

	/* Advance the frame state to be one more than
	the stored value */
    if (ptr->getFrame() != -1) {
        ptr->advanceFrame();
    }

	return true;
}


