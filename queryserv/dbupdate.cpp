/*	EQEMu: Everquest Server Emulator
	Copyright (C) 2001-2008 EQEMu Development Team (http://eqemulator.net)

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; version 2 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY except by those people which sell it, which
	are required to give you total support for your newly bought product;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR
	A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include "../common/global_define.h"
#include "../common/eqemu_logsys.h"
#include "../common/string_util.h"
#include "database.h"

#include <string.h>
#include <mysqld_error.h>

bool Database::DBSetup()
{
	if (!DBSetup_CheckLegacy())
	{
		return false;
	}
	return true;
}

#pragma region Merchant Tables
bool Database::Check_Merchant_Tables()
{
	std::string check_query1 = StringFormat("SHOW TABLES LIKE 'qs_merchant_transaction_record'");
	std::string check_query2 = StringFormat("SHOW TABLES LIKE 'qs_merchant_transaction_record_entries'");
	std::string check_query3 = StringFormat("SHOW TABLES LIKE 'qs_merchant_transaction_log'");
	auto results1 = QueryDatabase(check_query1);
	auto results2 = QueryDatabase(check_query2);
	auto results3 = QueryDatabase(check_query3);
	if (results1.RowCount() == 0 && results2.RowCount() == 0 && results3.RowCount() == 0)
	{
		if (!Create_Merchant_Table())
		{
			return false;
		}
	}
	else if (results3.RowCount() == 0)
	{
		if (!Create_Merchant_Table())
		{
			return false;
		}
	}

	if (results1.RowCount() != 0 && results2.RowCount() != 0)
	{
		if (Copy_Merchant_Record())
		{
			std::string drop_query1 = StringFormat("drop table if exists `qs_merchant_transaction_record`;");
			std::string drop_query2 = StringFormat("drop table if exists `qs_merchant_transaction_record_entries`;");
			auto drop_results1 = QueryDatabase(drop_query1);
			auto drop_results2 = QueryDatabase(drop_query2);
		}
	}
	return true;
}

bool Database::Create_Merchant_Table()
{
	Log.Out(Logs::General, Logs::QS_Server, "Attempting to create merchant table.");
	std::string query = StringFormat(
		"CREATE TABLE `qs_merchant_transaction_log` ( "
		"`char_id` int(11) DEFAULT '0', "
		"`char_slot` mediumint(7) DEFAULT '0', "
		"`item_id` int(11) DEFAULT '0', "
		"`charges` mediumint(7) DEFAULT '0', "
		"`zone_id` int(11) DEFAULT '0', "
		"`merchant_id` int(11) DEFAULT '0', "
		"`merchant_pp` int(11) DEFAULT '0', "
		"`merchant_gp` int(11) DEFAULT '0', "
		"`merchant_sp` int(11) DEFAULT '0', "
		"`merchant_cp` int(11) DEFAULT '0', "
		"`merchant_items` mediumint(7) DEFAULT '0', "
		"`char_pp` int(11) DEFAULT '0', "
		"`char_gp` int(11) DEFAULT '0', "
		"`char_sp` int(11) DEFAULT '0', "
		"`char_cp` int(11) DEFAULT '0', "
		"`char_items` mediumint(7) DEFAULT '0', "
		"`time` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP "
		") ENGINE = InnoDB DEFAULT CHARSET = utf8;");
	auto results = QueryDatabase(query);
	if (!results.Success())
	{
		Log.Out(Logs::General, Logs::QS_Server, "Error creating qs_merchant_transaction_log. \n%s", query.c_str());
		return false;
	}
	return true;
}

bool Database::Copy_Merchant_Record()
{
	std::string query1 = StringFormat("SELECT * from `qs_merchant_transaction_record`");
	auto results1 = QueryDatabase(query1);
	for (auto row = results1.begin(); row != results1.end(); ++row)
	{
		int32 transaction_id = atoi(row[0]);
		std::string time = row[1];
		int32 zone_id = atoi(row[2]);
		int32 merchant_id = atoi(row[3]);
		int32 merchant_pp = atoi(row[4]);
		int32 merchant_gp = atoi(row[5]);
		int32 merchant_sp = atoi(row[6]);
		int32 merchant_cp = atoi(row[7]);
		int32 merchant_items = atoi(row[8]);
		int32 char_id = atoi(row[9]);
		int32 char_pp = atoi(row[10]);
		int32 char_gp = atoi(row[11]);
		int32 char_sp = atoi(row[12]);
		int32 char_cp = atoi(row[13]);
		int32 char_items = atoi(row[14]);

		std::string query2 = StringFormat("SELECT * from `qs_merchant_transaction_record_entries` WHERE `event_id` = '%i'", transaction_id);
		auto results2 = QueryDatabase(query2);

		auto row2 = results2.begin();
		int32 event_id = atoi(row2[0]);
		int32 char_slot = atoi(row2[1]);
		int32 item_id = atoi(row2[2]);
		int32 charges = atoi(row2[3]);

		std::string query3 = StringFormat(
			"INSERT into qs_merchant_transaction_log SET "
				"char_id='%i', "
				"char_slot='%i', "
				"item_id='%i', "
				"charges='%i', "
				"zone_id='%i', "
				"merchant_id='%i', "
				"merchant_pp='%i', "
				"merchant_gp='%i', "
				"merchant_sp='%i', "
				"merchant_cp='%i', "
				"merchant_items='%i', "
				"char_pp='%i', "
				"char_gp='%i', "
				"char_sp='%i', "
				"char_cp='%i', "
				"char_items='%i', "
				"time='%s'",
				char_id,
				char_slot,
				item_id,
				charges,
				zone_id,
				merchant_id,
				merchant_pp,
				merchant_gp,
				merchant_sp,
				merchant_cp,
				merchant_items,
				char_pp,
				char_gp,
				char_sp,
				char_cp,
				char_items,
				time.c_str());

		Log.Out(Logs::Detail, Logs::QS_Server, "transaction_id: %i time: %s zone_id: %i\n"
			"merchant_id: %i merchant_pp: %i merchant_gp: %i merchant_sp: %i merchant_cp: %i merchant_cp: %i \n"
			"char_id: %i char_pp: %i char_gp: %i char_sp: %i char_cp: %i char_items: %i \n"
			"event_id: %i char_slot: %i item_id: %i charges: %i \n",
			transaction_id, time.c_str(), zone_id,
			merchant_id, merchant_pp, merchant_gp, merchant_sp, merchant_cp, merchant_items,
			char_id, char_pp, char_gp, char_sp, char_cp, char_items,
			event_id, char_slot, item_id, charges);

		auto results3 = QueryDatabase(query3);
		if (!results3.Success())
		{
			Log.Out(Logs::General, Logs::QS_Server, "Error copying to qs_merchant_transaction_log: \n%s", query3.c_str());
			return false;
		}
	}
	return true;
}
#pragma endregion

#pragma region Delete Tables
bool Database::Check_Delete_Tables()
{
	std::string check_query1 = StringFormat("SHOW TABLES LIKE 'qs_player_delete_record'");
	std::string check_query2 = StringFormat("SHOW TABLES LIKE 'qs_player_delete_record_entries'");
	std::string check_query3 = StringFormat("SHOW TABLES LIKE 'qs_player_Item_deletes'");
	auto results1 = QueryDatabase(check_query1);
	auto results2 = QueryDatabase(check_query2);
	auto results3 = QueryDatabase(check_query3);
	if (results1.RowCount() == 0 && results2.RowCount() == 0 && results3.RowCount() == 0)
	{
		if (!Create_Delete_Table())
		{
			return false;
		}
	}
	else if (results3.RowCount() == 0)
	{
		if (!Create_Delete_Table())
		{
			return false;
		}
	}

	if (results1.RowCount() != 0 && results2.RowCount() != 0)
	{
		if (Copy_Delete_Record())
		{
			std::string drop_query1 = StringFormat("drop table if exists `qs_player_delete_record`;");
			std::string drop_query2 = StringFormat("drop table if exists `qs_player_delete_record_entries`;");
			auto drop_results1 = QueryDatabase(drop_query1);
			auto drop_results2 = QueryDatabase(drop_query2);
		}
	}
	return true;
}

bool Database::Create_Delete_Table()
{
	Log.Out(Logs::General, Logs::QS_Server, "Attempting to create delete table.");
	std::string query = StringFormat(
		"CREATE TABLE `qs_player_Item_deletes` ( "
		"`char_id` int(11) DEFAULT '0', "
		"`char_slot` mediumint(7) DEFAULT '0', "
		"`item_id` int(11) DEFAULT '0', "
		"`charges` mediumint(7) DEFAULT '0', "
		"`stack_size` mediumint(7) DEFAULT '0', "
		"`char_items` mediumint(7) DEFAULT '0', "
		"`time` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP "
		") ENGINE = InnoDB DEFAULT CHARSET = utf8;");
	auto results = QueryDatabase(query);
	if (!results.Success())
	{
		Log.Out(Logs::General, Logs::QS_Server, "Error creating qs_player_Item_deletes. \n%s", query.c_str());
		return false;
	}
	return true;
}

bool Database::Copy_Delete_Record()
{
	std::string query1 = StringFormat("SELECT * from `qs_player_delete_record`");
	auto results1 = QueryDatabase(query1);
	for (auto row = results1.begin(); row != results1.end(); ++row)
	{
		int32 delete_id = atoi(row[0]);
		std::string time = row[1];
		int32 char_id = atoi(row[2]);
		int32 stack_size = atoi(row[3]);
		int32 char_items = atoi(row[4]);

		std::string query2 = StringFormat("SELECT * from `qs_player_delete_record_entries` WHERE `event_id` = '%i'", delete_id);
		auto results2 = QueryDatabase(query2);

		auto row2 = results2.begin();
		int32 event_id = atoi(row2[0]);
		int32 char_slot = atoi(row2[1]);
		int32 item_id = atoi(row2[2]);
		int32 charges = atoi(row2[3]);

		std::string query3 = StringFormat(
			"INSERT into qs_player_Item_deletes SET "
				"char_id='%i', "
				"char_slot='%i', "
				"item_id='%i', "
				"charges='%i', "
				"stack_size='%i', "
				"char_items='%i', "
				"time='%s'",
				char_id,
				char_slot,
				item_id,
				charges,
				stack_size,
				char_items,
				time.c_str());

		Log.Out(Logs::Detail, Logs::QS_Server, "delete_id: %i time: %s char_id: %i stack_size: %i char_items: %i \n"
			"event_id: %i char_slot: %i item_id: %i charges: %i \n",
			delete_id, time.c_str(), char_id, stack_size, char_items,
			event_id, char_slot, item_id, charges);

		auto results3 = QueryDatabase(query3);
		if (!results3.Success())
		{
			Log.Out(Logs::General, Logs::QS_Server, "Error copying to qs_player_Item_deletes: \n%s", query3.c_str());
			return false;
		}
	}
	return true;
}
#pragma endregion

bool Database::DBSetup_CheckLegacy()
{
	if (!Check_Delete_Tables())
	{
		return false;
	}
	if (!Check_Merchant_Tables())
	{
		return false;
	}
	Log.Out(Logs::General, Logs::QS_Server, "End of DBSetup_CheckLegacy migration.");
	return true;
}
