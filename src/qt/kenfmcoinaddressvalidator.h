// Copyright (c) 2011-2014 The KenFMcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KENFMCOIN_QT_KENFMCOINADDRESSVALIDATOR_H
#define KENFMCOIN_QT_KENFMCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class KenFMcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KenFMcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** KenFMcoin address widget validator, checks for a valid kenfmcoin address.
 */
class KenFMcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KenFMcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // KENFMCOIN_QT_KENFMCOINADDRESSVALIDATOR_H
