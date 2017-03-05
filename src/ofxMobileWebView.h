//
//  ofxMobileWebView.hpp
//
//  Created by Carlos Viejo on 23/02/2017.
//
#pragma once


#include "ofMain.h"
#include "ofxMobileWebViewEvent.h"
#if defined(TARGET_OF_IOS)
#include <WebKit/WebKit.h>
#include <UIKit/UIKit.h>
#endif


//--------------------------------------------------------------
class ofxMobileWebView : public ofRectangle {

	public:

		static ofEvent<ofxMobileWebViewEvent> events;

		ofxMobileWebView();
		~ofxMobileWebView();

		void show();
		void hide();
		void setRect(ofRectangle aRect);
		void loadUrl(string aUrl);
		void loadLocalFile(string aFile);
		void post(string aScript);

	private:

		bool       _visible = false;

#if defined(TARGET_OF_IOS)
		UIView*    _view;
		WKWebView* _webView;
#endif
};


#if defined(TARGET_OF_IOS)
//--------------------------------------------------------------
@interface ViewController : UIViewController <WKScriptMessageHandler>

@property (nonatomic, assign) ofxMobileWebView* listener;

@end
#endif

