 #ifndef BGMCONTROL_H
#define BGMCONTROL_H

#include <QObject>
#include <QMediaPlayer>
// #include <QMediaPlaylist>


class BGMControl : public QObject
{
    Q_OBJECT
public:
    explicit BGMControl(QObject *parent = nullptr);

signals:

private:
    // man woman
    QVector<QMediaPlayer*> m_players;
    // QVector<QMediaPlaylist*> m_lists;

};

#endif // BGMCONTROL_H
