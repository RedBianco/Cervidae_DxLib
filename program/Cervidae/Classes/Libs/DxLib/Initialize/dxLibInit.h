#pragma once


//=================================================================================//
//  dxLibInit.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/10/28.
//=================================================================================//


// DXライブラリが初期化されているか
bool	dxInit_IsDxLibInit( void );

// ウインドウモードで起動するか
bool	dxInit_CheckWindowModePlay( void );

// 低処理負荷モードで起動するか
bool	dxInit_CheckLowSpecModePlay( void );

// 低処理負荷モードかどうかでXAudioを使用するかどうかの設定を変更する
bool	dxInit_SpecModeSetEnableXAudioFlag( const int setFlag );

// メインウインドウが非アクティブ状態でも処理を実行するかどうか
int		dxInit_SetAlwaysActiveRunEnable( const int setFlag );

// ウインドウモードの時にウインドウのサイズを自由に変更出来るようにするかどうかを設定する
int     dxInit_WinSizeChangeSetEnable( const bool  bEnable = 0);

// メインウインドウが非アクティブ状態時の処理の実行設定
bool    dxInit_SetWindowAlwaysRunEnable( const int bEnable = 0);

// DXライブラリを使用したソフトの二重起動を可能にするかどうかの設定を行う( TRUE:可能にする FALSE:不可能にする( デフォルト ) )
bool	dxInit_SetDoubleStartValidEnable( const int bEnable = 0 );







/* End dxLibInit.h */