#pragma once


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



/* End dxLibInit.h */