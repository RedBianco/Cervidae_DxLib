#pragma once

//=================================================================================//
//  TaskLib.h
//  Cervidae
//
//  Created by kashima akihiro on 2019/06/06.
//=================================================================================//

/**
 *	@class 
 */
class TaskBase
{
public:
    virtual ~TaskBase(){}
    virtual void updateProcess( void ){}
    virtual void drawProcess( void ){}
};


/**
 *	@class 
 */
class TaskController
{
private:
    std::list<TaskBase*>	m_TaskList;

public:
    ~TaskController()
    {
		std::list<TaskBase*>::iterator it = m_TaskList.begin();
        for ( it; it != m_TaskList.end(); ++ it )
        {
			TaskBase* p_task = *it;
            delete p_task;
        }
    }
    /**
     * 
     */
    void AddTask( TaskBase* p_task )
    {
		if( p_task == nullptr ){
			return;
		}
		m_TaskList.push_back( p_task );
    }
    /**
     * 
     */
    void EraseTask( TaskBase* p_task )
    {
		if( p_task == nullptr ){
			return;
		}
        std::list<TaskBase*>::iterator it = std::find( m_TaskList.begin(), m_TaskList.end(), p_task );
        if ( it != m_TaskList.end() )
        {
            delete *it;
            m_TaskList.erase( it );
        }
    }
    /**
     * 
     */
    void Update( void )
    {
		std::list<TaskBase*>::iterator it = m_TaskList.begin();
        for ( it; it != m_TaskList.end(); ++ it )
        {
			TaskBase* p_task = *it;
            p_task->updateProcess();
        }
    }
    /**
     * 
     */
    void Draw( void )
    {
	/*	std::list<TaskBase*>::iterator it = m_TaskList.begin();
        for ( it; it != m_TaskList.end(); ++ it )
        {
			TaskBase* p_task = *it;
            p_task->drawProcess();
        }*/
		for ( std::list<TaskBase*>::iterator it = m_TaskList.begin(); it != m_TaskList.end(); ++ it )
        {
			TaskBase* p_task = *it;
            p_task->drawProcess();
        }
    }
};












