#pragma once

#include "YT_Interface.h"

class VideoViewList;

class RenderThread : public QThread
{
	Q_OBJECT;
public:
	
	RenderThread(YT_Renderer* renderer, VideoViewList* list);
	~RenderThread(void);

	void Start();
	void Stop();

	float GetSpeedRatio();
signals:

public slots:
	void RenderScene(QList<YT_Frame_Ptr> scene, unsigned int renderPTS); // pts set to INVALID_PTS when don't care about pts
	void SetLayout(QList<unsigned int>, QList<QRect>, QList<QRect>);

private slots:

protected:
	void run();
	void timerEvent(QTimerEvent *event);
	QList<YT_Frame_Ptr> RenderFrames(QList<YT_Frame_Ptr> sourceFrames, QList<YT_Frame_Ptr> renderFramesOld);

	float m_SpeedRatio;
	YT_Renderer* m_Renderer;
	VideoViewList* m_VideoViewList;

	// render queue
	QList<QList<YT_Frame_Ptr> > m_SceneQueue;
	QList<unsigned int> m_PTSQueue;

	// Last rendered scene
	QList<YT_Frame_Ptr> m_LastSourceFrames;
	QList<YT_Frame_Ptr> m_LastRenderFrames;
	unsigned int m_LastPTS;

	// Layout
	QList<unsigned int> m_ViewIDs;
	QList<QRect> m_SrcRects;
	QList<QRect> m_DstRects;

	QTime m_Timer;
};