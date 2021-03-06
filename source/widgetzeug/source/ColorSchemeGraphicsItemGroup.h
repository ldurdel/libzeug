#pragma once

#include <QGraphicsObject>
#include <QList>
#include <QMap>

#include <widgetzeug/ColorScheme.h>


class QGraphicsTextItem;
class QString;

namespace widgetzeug
{

class ColorScheme;
class ColorSchemeGraphicsItem;
class DpiAwareGraphicsView;

class ColorSchemeGraphicsItemGroup : public QGraphicsObject
{
    Q_OBJECT

public:
    ColorSchemeGraphicsItemGroup(const QString & identifier,
                                 const DpiAwareGraphicsView * view);

    virtual ~ColorSchemeGraphicsItemGroup();
    
    virtual QRectF boundingRect() const;
    
    virtual void paint(QPainter * painter, 
                       const QStyleOptionGraphicsItem * option, 
                       QWidget * widget = nullptr);

    void addScheme(ColorScheme * scheme);
    bool hasScheme(ColorScheme * scheme) const;
    ColorSchemeGraphicsItem * schemeGraphicsItem(ColorScheme * scheme) const;
    
    bool setSelected(ColorScheme * scheme);
    
    QList<ColorSchemeGraphicsItem *> schemeGraphicsItems() const;

    void update(ColorScheme::ColorSchemeTypes typeFilter, int classesFilter);
    void updateRects();

    void setDeficiency(ColorScheme::ColorVisionDeficiency deficiency);

protected slots:
    void onSelected(ColorScheme * scheme);
    
signals:
    void selected(ColorSchemeGraphicsItem * item);

private:
    void updateVisibility(ColorScheme::ColorSchemeTypes typeFilter, 
                          int classesFilter);

private:
    QGraphicsTextItem * m_label;
    const DpiAwareGraphicsView * m_view;

    QList<ColorScheme *> m_schemes;
    QMap<ColorScheme *, ColorSchemeGraphicsItem *> m_schemeGraphicsItems;

    ColorScheme::ColorSchemeTypes m_types;
    int m_minClasses, m_maxClasses;
};

} // namespace widgetzeug
