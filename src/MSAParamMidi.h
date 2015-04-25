/*
 *  MSAMidiParamManager.h
 *  Midi Controller Test
 *
 *  Created by Memo Akten on 21/08/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include "MSAParameter.h"
#include "MSAParamController.h"

namespace MSA {
	namespace Param {
		namespace Midi {
			
			void setup(int inputPort, int outputPort);

			
			//------------- Controller class
			class Controller : public MSA::Param::Controller {
			public:
				friend Controller* createController(int channel, int cc); 

				// from super
				void updateController();
				string toString();

				void receiveMidi(int channel, int cc, int newvalue);
				
			protected:
				Controller(int channel, int cc);// channel 0 means listen to all channels
				
				int		_channel;
				int		_cc;
			};

			
			Controller* createController(int channel, int cc);
			
			
		}
	}
}