/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __SCRIPT_EVENT_CENTER_H__
#define __SCRIPT_EVENT_CENTER_H__

#include <string>
#include "2d/CCNode.h"
#include "base/CCEventListenerTouch.h"

NS_CC_BEGIN

class CCTouchTargetNode;

#define CCTOUCHBEGAN        0
#define CCTOUCHMOVED        1
#define CCTOUCHENDED        2
#define CCTOUCHCANCELLED    3
#define CCTOUCHADDED        4
#define CCTOUCHREMOVED      5
#define ccTouchMax          6


/**
 * @addtogroup scene
 * @{
 */

/** @brief Scene is a subclass of Node that is used only as an abstract concept.

Scene and Node are almost identical with the difference that Scene has its
anchor point (by default) at the center of the screen.

For the moment Scene has no other logic than that, but in future releases it might have
additional logic.

It is a good practice to use a Scene as the parent of all your nodes.
*/
class CC_DLL ScriptEventCenter : public Node
{
public:
    /** creates a new Scene object */
    static ScriptEventCenter *create();

    void addTouchableNode(Node *node);
    void removeTouchableNode(Node *node);

    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *pEvent);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent);
    virtual void onTouchesCancelled(const std::vector<Touch*>& touches, Event *pEvent);

    // virtual void visit();
    virtual void cleanup(void);

    using Node::addChild;
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    ScriptEventCenter();
    virtual ~ScriptEventCenter();
    
    bool init();
    bool initWithSize(const Size& size);

protected:
    friend class Node;
    
    std::set<int> m_touchingIds;
    Vector<Node*> _touchableNodes;
    Vector<CCTouchTargetNode*> _touchingTargets;
    bool m_touchDispatchingEnabled;
    EventListenerTouchAllAtOnce *_touchListener;

    void sortAllTouchableNodes(Vector<Node*>&nodes);
    void enableTouchDispatching();
    void disableTouchDispatching();

    void dispatchingTouchEvent(const std::vector<Touch*>& touches, Event *pEvent, int event);
};

// end of ScriptEventCenter group
/// @}

NS_CC_END

#endif // __SCRIPT_EVENT_CENTER_H__
