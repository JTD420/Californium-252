// Copyright (c) 2011-2020 The Californium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CALIFORNIUM_QT_CALIFORNIUMADDRESSVALIDATOR_H
#define CALIFORNIUM_QT_CALIFORNIUMADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class CaliforniumAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit CaliforniumAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Californium address widget validator, checks for a valid californium address.
 */
class CaliforniumAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit CaliforniumAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // CALIFORNIUM_QT_CALIFORNIUMADDRESSVALIDATOR_H
