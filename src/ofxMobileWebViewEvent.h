//
//  ofxMobileWebViewEvent.h
//  WebViewTest
//
//  Created by Carlos Viejo on 23/02/2017.
//
//
#pragma once


#include "ofMain.h"


//--------------------------------------------------------------
class ofxMobileWebViewEvent : public ofEventArgs {

	public:

		enum EventType {
			WEBVIEW_MESSSAGE = 0
		};


		EventType type;
};
