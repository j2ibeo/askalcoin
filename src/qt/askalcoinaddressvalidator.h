// Copyright (c) 2011-2020 The Askalcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ASKALCOIN_QT_ASKALCOINADDRESSVALIDATOR_H
#define ASKALCOIN_QT_ASKALCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class AskalcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AskalcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Askalcoin address widget validator, checks for a valid askalcoin address.
 */
class AskalcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AskalcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // ASKALCOIN_QT_ASKALCOINADDRESSVALIDATOR_H
