// BorderlessWindow.hpp
#pragma once

#include <QtQuick/QQuickWindow>

class BorderlessWindow : public QQuickWindow
{
    Q_OBJECT
    Q_PROPERTY(int titleHeight READ titleHeight WRITE setTitleHeight NOTIFY titleHeightChanged)

public:
    explicit BorderlessWindow(QWindow *parent = nullptr);
    explicit BorderlessWindow(QQuickRenderControl *renderControl);

    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

    void setTitleHeight(int value);
    int titleHeight() const;

signals:
    void titleHeightChanged();

private:
    HRESULT hit_test(POINT point) const;
    bool composition_enabled() const;

    int m_titleHeight = 20;
};
