#pragma once

//=================================================================================//
//  TaskCore.h
//  Cervidae
//
//  Created by kashima akihiro on 2019/06/06.
//=================================================================================//

typedef enum {
	eAPP_TASK_GROUP_START = 0,
	eAPP_TASK_GROUP_MOVIE = 1,

	ENUM_APP_TASK_GROUP_MAX

} ENUM_APP_TASK_GROUP_LIST;

// タスクの実行優先順位の最大値 - 1
#define TASK_PRIORITY_MAX		(16)

/**
 *	タスクの基本情報
 */
typedef struct _STaskBaseInfo
{
	// 状態推移処理の実行優先順位
	int StepPriority;
	// 描画処理の実行優先順位
	int RenderPriority;
	// 状態推移処理を行う関数へのポインタ
	bool (*Step)( struct _STaskInfo* TInfo, float StepTime );
	// 描画処理を行う関数へのポインタ
	void (*Render)( struct _STaskInfo* TInfo );
	// 後始末処理を行う関数へのポインタ
	void (*Terminate)( struct _STaskInfo* TInfo );
} STaskBaseInfo;

/**
 *	各タスクの情報
 */
typedef struct _STaskInfo
{
	// タスクの基本情報へのポインタ
	STaskBaseInfo*	Base;
	// タスクが使用するデータへのポインタ
	void*			Data;
	// 状態推移処理の実行優先順位が同じタスクのリストの次のタスクへのポインタ
	struct _STaskInfo* StepNext;
	// 描画処理の実行優先順位が同じタスクのリストの次のタスクへのポインタ
	struct _STaskInfo* RenderNext;
	// 追加又は削除するタスクのリストの次のタスクへのポインタ
	struct _STaskInfo* AddOrDelNext;
} STaskInfo;

/**
 *	タスクシステム情報
 */
typedef struct _STaskSystemInfo
{
	// タスクの処理を実行中かどうかのフラグ
	bool		Run;
	// 状態推移処理のタスクのリストの各優先順位の先頭タスクへのポインタ
	STaskInfo*	StepTask[TASK_PRIORITY_MAX];
	// 描画処理のタスクのリストの各優先順位の先頭タスクへのポインタ
	STaskInfo*	RenderTask[TASK_PRIORITY_MAX];
	// 追加するタスクのリストの先頭タスクへのポインタ
	STaskInfo*	AddTaskList;
	// 削除するタスクのリストの先頭タスクへのポインタ
	STaskInfo*	DelTaskList;
} STaskSystemInfo;

/**
 *	タスク管理
 */
namespace App
{
	class TaskManager
	{
	public:
		TaskManager();
		~TaskManager();

	public:
		// タスクシステムの初期化
		void	TaskSystem_Initialize(
			STaskSystemInfo* TSysInfo			// タスクシステム情報構造体のアドレス
		);
		// タスクシステムの後始末
		void	TaskSystem_Terminate(
			STaskSystemInfo* TSysInfo			// タスクシステム情報構造体のアドレス
		);
		// タスクシステムの状態推移処理を実行する
		//     戻り値 : 処理が正常に終了したかどうか(true:正常に終了した  false:エラーが発生した)
		bool	TaskSystem_Step(
			STaskSystemInfo* TSysInfo,			// タスクシステム情報構造体のアドレス
			float StepTime						// 推移させる時間( 単位：秒 )
		);
		// タスクシステムの描画処理を実行する
		void	TaskSystem_Render(
			STaskSystemInfo* TSysInfo			// タスクシステム情報構造体のアドレス
		);
		// タスクシステムにタスクを追加する
		void	TaskSystem_AddTask(
			STaskSystemInfo* TSysInfo,			// タスクシステム情報構造体のアドレス
			STaskInfo* TInfo					// 追加するタスクの情報構造体のアドレス
		);
		// タスクシステムに登録したタスクを削除する
		void	TaskSystem_DelTask(
			STaskSystemInfo* TSysInfo,			// タスクシステム情報構造体のアドレス
			STaskInfo* TInfo					// 削除するタスクの情報構造体のアドレス
		);
	};
}
















