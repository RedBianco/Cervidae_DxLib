#pragma once

//===================================================================================
//  appScene_Base.h
//  Cervidae
//
//  Created by kashima akihiro on 2019/11/29.
//===================================================================================

namespace App
{
	class SceneBase
	{
	public:
		// 各シーン画面の状態推移処理を行う
		//     戻り値 : 処理が正常に終了したかどうか(true:正常に終了した  false:エラーが発生した)
		virtual bool Task_Step(
			STaskInfo* TInfo,		// タスクシステム情報構造体のアドレス
			float StepTime			// 推移させる時間( 単位：秒 )
		) = 0;
		// 各シーン画面の描画処理を行う
		virtual void Task_Render(
			STaskInfo* TInfo		// タスクシステム情報構造体のアドレス
		) = 0;
		// 各シーン画面の後始末処理を行う
		virtual void Task_Terminate(
			STaskInfo* TInfo		// タスクシステム情報構造体のアドレス
		) = 0;

		// タスクの登録処理

	};
}

/* End appScene_Base.h */




