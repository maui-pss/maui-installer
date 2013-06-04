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

#include <QtCore/QLocale>

#include "languagesmodel.h"

LanguagesModel::LanguagesModel(QObject *parent)
    : QAbstractListModel(parent)
{
    // Languages we always want
    m_langs.append("en_US");
    m_langs.append("en_GB");
    m_langs.append("de_DE");
    m_langs.append("fr_FR");
    m_langs.append("es_ES");
    m_langs.append("zh_CN");
    m_langs.append("ja_JP");
    m_langs.append("ru_RU");
    m_langs.append("ar_EG");

    // Add current locale;
    QLocale currentLocale = QLocale::system();
    if (currentLocale.name() != QStringLiteral("C"))
        m_langs.append(currentLocale.name());
}

QHash<int, QByteArray> LanguagesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CodeRole] = "code";
    roles[NameRole] = "name";
    return roles;
}

int LanguagesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_langs.size();
}

QVariant LanguagesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QString code = m_langs.at(index.row());
    QLocale locale(code);

    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return locale.nativeLanguageName();
    case CodeRole:
        return code;
    default:
        break;
    }

    return QVariant();
}

#include "moc_languagesmodel.cpp"
