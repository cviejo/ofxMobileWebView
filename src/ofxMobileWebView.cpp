//
//  ofxMobileWebView.cpp
//
//  Created by Carlos Viejo on 23/02/2017.
//
#include "ofxMobileWebView.h"
#if defined(TARGET_OF_IOS)
#include "ofxiPhoneExtras.h"
#endif


ofEvent<ofxMobileWebViewEvent> ofxMobileWebView::events;


//--------------------------------------------------------------
ofxMobileWebView::ofxMobileWebView(){

	WKWebViewConfiguration* config     = [[WKWebViewConfiguration alloc]  init];
	ViewController*         controller = [[ViewController alloc] init];

	controller.listener = this;

	[config.userContentController addScriptMessageHandler:controller name:@"observe"];

#if defined(TARGET_OF_IOS)
	CGRect frame = CGRectMake(0, 0, ofGetWidth(), ofGetHeight() - 100);

	_view    = [[UIView alloc]    initWithFrame:frame];
	_webView = [[WKWebView alloc] initWithFrame:frame configuration:config];

	_webView.tag = 0;
	_webView.scrollView.scrollEnabled = NO;
	_webView.scrollView.bounces = NO;
	_webView.autoresizingMask = UIViewAutoresizingFlexibleRightMargin |
	                            UIViewAutoresizingFlexibleBottomMargin |
	                            UIViewAutoresizingFlexibleWidth |
	                            UIViewAutoresizingFlexibleHeight;

	[_view addSubview:_webView];
#endif

	this->show();
}


//--------------------------------------------------------------
ofxMobileWebView::~ofxMobileWebView(){

	this->hide();

#if defined(TARGET_OF_IOS)
	[_view release];
	[_webView release];
#endif
}


//--------------------------------------------------------------
void ofxMobileWebView::setRect(ofRectangle aRect){

	this->set(aRect);

#if defined(TARGET_OF_IOS)
	[_view setFrame:CGRectMake(this->x, this->y, this->width, this->height)];
#endif
}

//--------------------------------------------------------------
void ofxMobileWebView::show(){

	if (!_visible){

		_visible = true;

#if defined(TARGET_OF_IOS)
		[ofxiPhoneGetGLParentView() addSubview:_view];
#endif
	}
}


//--------------------------------------------------------------
void ofxMobileWebView::hide(){

	if (_visible){

		_visible = false;

#if defined(TARGET_OF_IOS)
		[_view removeFromSuperview];
#endif
	}
}


//--------------------------------------------------------------
void ofxMobileWebView::loadUrl(string aUrl){

	NSString* urlString = [NSString stringWithCString:aUrl.c_str() encoding:[NSString defaultCStringEncoding]];
	NSURL*    url       = [NSURL URLWithString:urlString];
	
	[[NSURLCache sharedURLCache] removeAllCachedResponses];
	[_webView loadRequest:[NSURLRequest requestWithURL:url]];
}


//--------------------------------------------------------------
void ofxMobileWebView::loadLocalFile(string aFile){

	NSString* filename   = [NSString stringWithCString:aFile.c_str() encoding:[NSString defaultCStringEncoding]];
	NSString* bundlePath = [[NSBundle mainBundle] bundlePath];
	NSURL*    rootUrl    = [NSURL fileURLWithPath:bundlePath];
	NSString* filepath   = [[NSBundle mainBundle] pathForResource:filename ofType:@"html" inDirectory:@"www"];
	NSString* htmlString = [NSString stringWithContentsOfFile:filepath encoding:NSUTF8StringEncoding error:nil];

	[_webView loadHTMLString:htmlString baseURL:rootUrl];
}


//--------------------------------------------------------------
void ofxMobileWebView::post(string aScript){

	NSString* script = [NSString stringWithCString:aScript.c_str() encoding:[NSString defaultCStringEncoding]];

	[_webView evaluateJavaScript:script completionHandler:nil];
}


@interface ViewController ()

@end

@implementation ViewController


- (void)userContentController:(WKUserContentController *)controller didReceiveScriptMessage:(WKScriptMessage *)message {

    if ([message.name isEqualToString:@"observe"]) {

        std::string temp = std::string([message.body UTF8String]);

        ofLogVerbose() << temp;
    }
}
@end


