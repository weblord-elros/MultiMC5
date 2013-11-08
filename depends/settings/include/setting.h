/* Copyright 2013 MultiMC Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <QObject>
#include <QVariant>

#include "libsettings_config.h"

class SettingsObject;

/*!
 *
 */
class LIBSETTINGS_EXPORT Setting : public QObject
{
	Q_OBJECT
public:
	/*!
	 * \brief Constructs a new Setting object with the given parent.
	 * \param parent The Setting's parent object.
	 */
	explicit Setting(QString id, QVariant defVal = QVariant(), QObject *parent = 0);

	/*!
	 * \brief Gets this setting's ID.
	 * This is used to refer to the setting within the application.
	 * \warning Changing the ID while the setting is registered with a SettingsObject results in
	 * undefined behavior.
	 * \return The ID of the setting.
	 */
	virtual QString id() const
	{
		return m_id;
	}

	/*!
	 * \brief Gets this setting's config file key.
	 * This is used to store the setting's value in the config file. It is usually
	 * the same as the setting's ID, but it can be different.
	 * \return The setting's config file key.
	 */
	virtual QString configKey() const
	{
		return id();
	}

	/*!
	 * \brief Gets this setting's value as a QVariant.
	 * This is done by calling the SettingsObject's retrieveValue() function.
	 * If this Setting doesn't have a SettingsObject, this returns an invalid QVariant.
	 * \return QVariant containing this setting's value.
	 * \sa value()
	 */
	virtual QVariant get() const;

	/*!
	 * \brief Gets this setting's actual value (I.E. not as a QVariant).
	 * This function is just shorthand for get().value<T>()
	 * \return The setting's actual value.
	 */
	template <typename T> inline T value() const
	{
		return get().value<T>();
	}

	/*!
	 * \brief Gets this setting's default value.
	 * \return The default value of this setting.
	 */
	virtual QVariant defValue() const;

signals:
	/*!
	 * \brief Signal emitted when this Setting object's value changes.
	 * \param setting A reference to the Setting that changed.
	 * \param value This Setting object's new value.
	 */
	void settingChanged(const Setting &setting, QVariant value);

	/*!
	 * \brief Signal emitted when this Setting object's value resets to default.
	 * \param setting A reference to the Setting that changed.
	 */
	void settingReset(const Setting &setting);

public
slots:
	/*!
	 * \brief Changes the setting's value.
	 * This is done by emitting the settingChanged() signal which will then be
	 * handled by the SettingsObject object and cause the setting to change.
	 * \param value The new value.
	 */
	virtual void set(QVariant value);

	/*!
	 * \brief Reset the setting to default
	 * This is done by emitting the settingReset() signal which will then be
	 * handled by the SettingsObject object and cause the setting to change.
	 * \param value The new value.
	 */
	virtual void reset();

protected:
	QString m_id;
	QVariant m_defVal;
};
