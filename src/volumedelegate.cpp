/****************************************************************************
 * This file is part of Maui Installer.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QApplication>
#include <QPainter>
#include <QPixmap>
#include <QPointer>
#include <QTextDocument>

#include <solid/device.h>
#include <solid/storagevolume.h>

#include "volumedelegate.h"
#include "volumemodel.h"

const quint32 kLateralMargin = 4;

VolumeDelegate::VolumeDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
    , m_iconSize(QSize(64, 64))
{
}

void VolumeDelegate::paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    bool isLTR = option.direction == Qt::LeftToRight;
    const VolumeModel *model = qobject_cast<const VolumeModel *>(index.model());
    Solid::Device device = const_cast<VolumeModel *>(model)->device(index);
    QPointer<Solid::StorageVolume> volume = device.as<Solid::StorageVolume>();
    QIcon icon = model->icon(index);
    QString text = model->text(index);

    painter->save();

    // Draw primitive element
    QStyleOptionViewItemV4 opt = option;
    QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter, opt.widget);

    // Draw icon
    QPixmap pm = icon.pixmap(m_iconSize);
    QPoint point(isLTR ? option.rect.left() + kLateralMargin
                       : option.rect.right() - kLateralMargin - m_iconSize.height(),
                 option.rect.top() + (option.rect.height() - m_iconSize.height()) / 2);
    painter->drawPixmap(point, pm);

    // Text color when the item is selected
    if (option.state & QStyle::State_Selected) {
        QPalette::ColorGroup cg = QPalette::Active;
        if (!(option.state & QStyle::State_Enabled))
            cg = QPalette::Disabled;
        else if (!(option.state & QStyle::State_Active))
            cg = QPalette::Inactive;
        painter->setPen(option.palette.color(cg, QPalette::HighlightedText));
    }

    // TODO: capacity bar

    QTextDocument document;
    QString html = QString::fromUtf8("<strong>%1</strong><br />%2")
            .arg(text).arg(representSize(volume.data()->size()));
    document.setHtml(html);

    // Calculate positioning
    int x = option.rect.left() + m_iconSize.width() + kLateralMargin * 2;
    int y = option.rect.top() + kLateralMargin;

    painter->translate(x, y);
    document.drawContents(painter, QRectF(QPointF(0, 0), option.rect.size() -
                                          QSize(m_iconSize.width() + kLateralMargin, 0)));

    painter->restore();
}

QSize VolumeDelegate::sizeHint(const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
    Q_UNUSED(index);

    QTextDocument document;
    document.setHtml(QStringLiteral("<strong>Really long label</strong><br />"
                                    "999.99 GiB"));
    return QSize(m_iconSize.width() + kLateralMargin * 2 + document.textWidth(),
                 m_iconSize.height() + kLateralMargin * 2);

    return QSize(option.rect.width(), option.fontMetrics.height() / 2
                 + qMax(m_iconSize.width(), option.fontMetrics.height()));
}

QString VolumeDelegate::representSize(qulonglong size) const
{
    QLocale locale;

    qreal kib = size / 1024.0;
    if (kib < 1.0)
        return QCoreApplication::translate(
                    "VolumeDelegate",
                    "%1 bytes", "Bytes format").arg(locale.toString(size));

    qreal mib = kib / 1024.0;
    if (mib < 1.0)
        return QCoreApplication::translate(
                    "VolumeDelegate",
                    "%1 KiB", "File size format").arg(locale.toString(kib, 'f', 3));

    qreal gib = mib / 1024.0;
    if (gib < 1.0)
        return QCoreApplication::translate(
                    "VolumeDelegate",
                    "%1 MiB", "File size format").arg(locale.toString(mib, 'f', 3));

    qreal tib = gib / 1024.0;
    if (tib < 1.0)
        return QCoreApplication::translate(
                    "VolumeDelegate",
                    "%1 GiB", "File size format").arg(locale.toString(gib, 'f', 3));

    qreal pib = tib / 1024.0;
    if (pib < 1.0)
        return QCoreApplication::translate(
                    "VolumeDelegate",
                    "%1 TiB", "File size format").arg(locale.toString(tib, 'f', 3));

    return QCoreApplication::translate(
                "VolumeDelegate",
                "%1 PiB", "File size format").arg(locale.toString(pib, 'f', 3));
}

#include "moc_volumedelegate.cpp"
