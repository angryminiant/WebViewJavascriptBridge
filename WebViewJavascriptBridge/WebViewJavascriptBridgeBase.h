//
//  WebViewJavascriptBridgeBase.h
//
//  Created by @LokiMeyburg on 10/15/14.
//  Copyright (c) 2014 @LokiMeyburg. All rights reserved.
//

#import <Foundation/Foundation.h>

// url.scheme
//文件WebViewJavascriptBridge_JS中 CUSTOM_PROTOCOL_SCHEME
//文件ExampleApp中 WVJBIframe.src
#define kOldProtocolScheme @"wvjbscheme"
#define kNewProtocolScheme @"https"

// url.host
#define kQueueHasMessage   @"__wvjb_queue_message__"
#define kBridgeLoaded      @"__bridge_loaded__"


/// WVJB js->oc后，oc回调js的block
typedef void (^WVJBResponseCallback)(id responseData);

/// WVJB js->oc 方法参数回调block
/// @param data oc方法名，oc方法参数等，可自定义数据对应关系，
/// @param responseCallback oc回调js的block
typedef void (^WVJBHandler)(id data, WVJBResponseCallback responseCallback);

/// 定义一个WVJB消息类型为字典的别名
typedef NSDictionary WVJBMessage;


/// 声明WVJB的Base协议
/// @note UIWebView 和 WKWebView 的JavaScriptBridge类都得实现这个协议
@protocol WebViewJavascriptBridgeBaseDelegate <NSObject>

/// 评估执行js语句
/// @param javascriptCommand js语句
/// @return 评估执行结果
- (NSString*) _evaluateJavascript:(NSString*)javascriptCommand;

@end


/// Base
/// @note UIWebView 和 WKWebView 的JavaScriptBridge类中定义base，并将自身设置为base的协议代理对象
@interface WebViewJavascriptBridgeBase : NSObject


@property (weak, nonatomic) id <WebViewJavascriptBridgeBaseDelegate> delegate;
@property (strong, nonatomic) NSMutableArray* startupMessageQueue;
@property (strong, nonatomic) NSMutableDictionary* responseCallbacks;
@property (strong, nonatomic) NSMutableDictionary* messageHandlers;
@property (strong, nonatomic) WVJBHandler messageHandler;

+ (void)enableLogging;
+ (void)setLogMaxLength:(int)length;

- (void)reset;

- (void)sendData:(id)data responseCallback:(WVJBResponseCallback)responseCallback handlerName:(NSString*)handlerName;

- (void)flushMessageQueue:(NSString *)messageQueueString;

- (void)injectJavascriptFile;


- (BOOL)isWebViewJavascriptBridgeURL:(NSURL*)url;
- (BOOL)isQueueMessageURL:(NSURL*)urll;
- (BOOL)isBridgeLoadedURL:(NSURL*)urll;
- (void)logUnkownMessage:(NSURL*)url;
- (NSString *)webViewJavascriptCheckCommand;
- (NSString *)webViewJavascriptFetchQueyCommand;
- (void)disableJavscriptAlertBoxSafetyTimeout;

@end
