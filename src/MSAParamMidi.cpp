/*
 *  MSAMidiParamManager.cpp
 *  Midi Controller Test
 *
 *  Created by Memo Akten on 21/08/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#include "MSAParamMidi.h"
#include "ofxMidi.h"

namespace MSA {
	namespace Param {
		namespace Midi {
			
			//----------- GLOBALS ---------------------
			
			ofxMidiIn			midiIn;
			ofxMidiOut			midiOut;
			bool				isSetup = false;
			vector<Controller*>	controllers;
			
			
			//----------- MIDI LISTENER ---------------------
			class Listener : public ofxMidiListener {
			protected:	
				void newMidiMessage(ofxMidiEventArgs& e) {
//					printf("newMidiMessage: %i %i %i %i %i\n", e.port, e.channel, e.status, e.byteOne, e.byteTwo);
					switch(e.status) {
						case MIDI_CONTROL_CHANGE:
							for(int i=0; i<controllers.size(); i++) controllers[i]->receiveMidi(e.channel, e.byteOne, e.byteTwo);
							break;
							
						case MIDI_NOTE_ON:
							break;
					}
				}
			} listener;
			

			
			void setup(int inputPort, int outputPort) {
				midiIn.listPorts();
				midiIn.openPort(inputPort);
				midiIn.addListener(&listener);
				
				midiOut.listPorts();
				midiOut.openPort(outputPort);
				
				isSetup = true;
			}
			
			Controller* createController(int channel, int cc) {
				Controller *c = new Controller(channel, cc);
				controllers.push_back(c);
				return c;
			}

			
			void sendCC(int channel, int cc, int value) {
//				if(!isSetup) setup(0, 0);
				midiOut.sendControlChange(channel, cc, value);
			}
			
			
			
			//--------------- CONTROLLER ----------------------------
			Controller::Controller(int channel, int cc):
			_channel(channel),
			_cc(cc) 
			{}
			
			//		void Controller::valueChanged() {
			//			sendMidi();
			//		}
			
			void Controller::updateController() {
//				printf(" *** SENDING MIDI FOR PARAM %i, %i\n", _channel, _cc);
				sendCC(_channel, _cc, _param->mappedTo(0, 127));
			}
			
			string Controller::toString() {
				return ofToString(_cc);
			}
			
			void Controller::receiveMidi(int channel, int cc, int newvalue) {
				// if (channel == 0) accept all channels, otherwise check to see if channel is correct
				if(_channel && _channel != channel) return;
				
				if(_cc == cc) {
					_param->setMappedFrom(newvalue, 0, 127);
				}
			}

			
		}
	}
}