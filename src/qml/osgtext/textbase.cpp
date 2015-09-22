#include "textbase.hpp"
#include "textbaseindex.hpp"

#include <osgQtQml/Index>

#include <osgText/TextBase>

#include <QDebug>

/*!
   \qmltype TextBase
   \inherits osg::Drawable
   \inqmlmodule osgText
   \brief Base type for text \l {osg::Node}{Nodes}
 */

namespace osgText {

TextBaseQtQml::Index::Index(TextBase *drawable) :
    DrawableQtQml::Index(drawable),
    qthis(0),
    characterSize(0)
{
    othis = drawable;
}

void TextBaseQtQml::Index::classBegin()
{
    DrawableQtQml::Index::othis = othis;
    DrawableQtQml::Index::qthis = qthis;

    DrawableQtQml::Index::classBegin();
}

void TextBaseQtQml::Index::componentComplete()
{
    DrawableQtQml::Index::othis = othis;
    DrawableQtQml::Index::qthis = qthis;

    DrawableQtQml::Index::componentComplete();
}

void TextBaseQtQml::Index::setColor(const QColor &color)
{
    osg::Vec4 c = osgQt::swapColor(color);

    if(othis->getColor() == c) return;

    othis->setColor(c);

    emit qthis->colorChanged(color);
}

TextBaseQtQml::TextBaseQtQml(QObject *parent) :
  DrawableQtQml(parent)
{
}

TextBaseQtQml::TextBaseQtQml(TextBaseQtQml::Index *index, QObject *parent) :
  DrawableQtQml(index, parent)
{
}

void TextBaseQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    DrawableQtQml::classBegin();
}

/*!
   \qmlproperty osgText::Style osgText::TextBase::style

   Text \l {osgText::Style}{style}
 */

StyleQtQml *TextBaseQtQml::getStyle() const
{
    return StyleQtQml::fromStyle(static_cast<Index*>(i)->othis->getStyle());
}

void TextBaseQtQml::setStyle(StyleQtQml *style)
{
    if(static_cast<Index*>(i)->othis->getStyle() == style->style()) return;

    static_cast<Index*>(i)->othis->setStyle(style->style());

    emit styleChanged(style);
}

/*!
   \qmlproperty color osgText::TextBase::color

   Color of \l {osgText::TextBase}{text}
 */

QColor TextBaseQtQml::getColor() const
{
    return osgQt::swapColor(static_cast<Index*>(i)->othis->getColor());
}

void TextBaseQtQml::setColor(const QColor &color)
{
    static_cast<Index*>(i)->setColor(color);
}

/*!
   \qmlproperty string osgText::TextBase::text

   The the text string
 */

QString TextBaseQtQml::getText() const
{
    return osgQt::swapString(static_cast<Index*>(i)->othis->getText());
}

void TextBaseQtQml::setText(const QString &text)
{
    QString qText = getText();

    if(text == qText) return;

    static_cast<Index*>(i)->othis->setText(osgQt::swapString(text));

    emit textChanged(text);
}

/*!
   \qmlproperty real osgText::TextBase::characterSize

   The the rendered character size in object coordinates
 */

qreal TextBaseQtQml::getCharacterSize() const
{
    return static_cast<qreal>(static_cast<Index*>(i)->characterSize);
}

void TextBaseQtQml::setCharacterSize(qreal size)
{
    if(static_cast<Index*>(i)->characterSize == size) return;

    // NOTE: osgText::TextBase has not getCharacterSize method?...
    // We cache it in index object now
    static_cast<Index*>(i)->characterSize = size;
    static_cast<Index*>(i)->othis->setCharacterSize(static_cast<float>(size));

    emit characterSizeChanged(size);
}

TextBaseQtQml::AxisAlignment TextBaseQtQml::getAxisAlignment() const
{
    return static_cast<AxisAlignment>(static_cast<Index*>(i)->othis->getAxisAlignment());
}

void TextBaseQtQml::setAxisAlignment(TextBaseQtQml::AxisAlignment axisAlignment)
{
    if(getAxisAlignment() == axisAlignment) return;

    static_cast<Index*>(i)->othis->setAxisAlignment(static_cast<TextBase::AxisAlignment>(axisAlignment));

    emit axisAlignmentChanged(axisAlignment);
}

TextBaseQtQml::DrawModeMasks TextBaseQtQml::getDrawMode() const
{
    return DrawModeMasks(static_cast<Index*>(i)->othis->getDrawMode());
}

void TextBaseQtQml::setDrawMode(TextBaseQtQml::DrawModeMasks drawMode)
{
    if(getDrawMode() == drawMode) return;

    static_cast<Index*>(i)->othis->setDrawMode(static_cast<TextBase::DrawModeMask>(static_cast<int>(drawMode)));

    emit drawModeChanged(drawMode);
}

TextBase *TextBaseQtQml::textBase()
{
    return static_cast<Index*>(i)->othis;
}

TextBaseQtQml *TextBaseQtQml::fromTextBase(TextBase *textBase, QObject *parent)
{
    if(!textBase) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(textBase))
    {
        return static_cast<Index*>(index)->qthis;
    }

    TextBaseQtQml *result = new TextBaseQtQml(new Index(textBase), parent);
    result->classBegin();
    return result;
}

}
