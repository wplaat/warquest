<?php

/* 
**  ========
**  WARQUEST
**  ========
**
**  Created by wplaat
**
**  For more information visit the following website.
**  Website : www.plaatsoft.nl 
**
**  Or send an email to the following address.
**  Email   : info@plaatsoft.nl
**
**  All copyrights reserved (c) 2008-2013 PlaatSoft
*/

/*
** ---------
** MAIN MENU
** ---------
*/

function warquest_ui_mainmenu() {
	
	/* input */
	global $mid;
	global $config;
	global $player;
	global $skill;
	
	/* Count not accepted recruit request */
	$query  = 'select pid1 from player_player where approved=0 and pid2='.$player->pid; 
	$result = warquest_db_query($query);
	$recruit = warquest_db_num_rows($result);	
	
	$query2 = 'select ugid from unit_group where type=2 and planet='.$player->planet;
	$result2 = warquest_db_query($query2);
	$data2 = warquest_db_fetch_object($result2);

	$query3 = 'select bgid from building_group where planet='.$player->planet.' order by bgid limit 1';
	$result3 = warquest_db_query($query3);
	$data3 = warquest_db_fetch_object($result3);
			
	$page  = '<div class="menu">';
	
	$page .= warquest_ui_menu(MENU_HOME, PAGE_OVERVIEW, 0, t('LINK_HOME'), $mid, 
					$player->news + $player->comment + $skill->skill_points);
	
	if ($player->holiday_date <= date("Y-m-d H:i:s", time())) {
		
		$page .= warquest_ui_menu(MENU_MISSIONS, warquest_get_default_mission($player->planet), 0, t('LINK_MISSIONS'), $mid);
	
		$page .= warquest_ui_menu(MENU_BATTLE, PAGE_ENEMIES, 0, t('LINK_BATTLE'), $mid);

		$page .= warquest_ui_menu(MENU_UNITS, $data2->ugid, 0, t('LINK_UNITS'), $mid);
			
		$page .= warquest_ui_menu(MENU_BUILDINGS, $data3->bgid, 0, t('LINK_BUILDINGS'), $mid);

		$page .= warquest_ui_menu(MENU_MONEY, PAGE_BANK, 0, t('LINK_MONEY'), $mid);
			
	}
		
	$page .= warquest_ui_menu(MENU_ALLIANCE, PAGE_PENDING, 0, t('LINK_ALLIANCE'), $mid, $recruit);
		
	$page .= warquest_ui_menu(MENU_FORUMS, PAGE_FORUM, 0, t('LINK_FORUM'), $mid);
	
	$page .= warquest_ui_menu(MENU_HELP, PAGE_INSTRUCTIONS, 0, t('LINK_HELP'), $mid);

	if ($player->pid==$config["adminPid"]) {
		$page .= warquest_ui_menu(MENU_ADMIN, PAGE_PLAYER_LIST, 0, t('LINK_ADMIN'), $mid);	
	}
	
	$page .= '</div>';	
			
	return $page;
}

/*
** ---------------
** LOGIN MENU
** ---------------
*/

/**
 * Login menu bar
 */
function warquest_login_menu() {

	/* input */
	global $mid;
	global $sid;
	global $version;
	
	$page  = '<center>';
		
	$page .= warquest_ui_menu($mid, PAGE_LOGIN, 0, t('LINK_LOGIN'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_REGISTER, 0, t('LINK_REGISTER'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_RECOVER, 0, t('LINK_RECOVER'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_FACEBOOK, 0,  t('LINK_FACEBOOK'), $sid);
		
	if (strlen($version)==0) {
		$page .= '<a target="_blank" href="rss.php">'.t('LINK_RSS').'</a>'; 
	}
		
	$page .= '</center>';
	
	return $page;
}
	
/*
** ---------------
** HOME SUBMENU
** ---------------
*/

function warquest_menu_home() {

	/* input */
	global $mid;
	global $sid;
	global $skill;
	global $player;
				
	$page  = '<div class="submenu">';
				
	$page .= warquest_ui_menu($mid, PAGE_OVERVIEW, 0, t('LINK_OVERVIEW'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_PROFILE, 0, t('LINK_PROFILE'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_BATTLE_NEWS, 0, t('LINK_NEWS'), $sid, $player->news);
	$page .= warquest_ui_menu($mid, PAGE_MESSAGES, 0, t('LINK_COMMENTS'), $sid, $player->comment);
	$page .= warquest_ui_menu($mid, PAGE_SKILLS, 0, t('LINK_SKILLS'), $sid, $skill->skill_points);
	$page .= warquest_ui_menu($mid, PAGE_RESTORE, 0, t('LINK_RESTORE'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_TRADE, 0, t('LINK_TRADE'), $sid );
	$page .= warquest_ui_menu($mid, PAGE_SETTINGS, 0, t('LINK_SETTINGS'), $sid);
	
	$member=warquest_db_member($player->pid);
	if ($member->auto_login==0) {
		$link = warquest_link('mid='.MENU_LOGIN.'&sid='.PAGE_LOGIN.'&eid=4', t('LINK_LOGOUT'), "logout");
		$page .= $link.' ';
	}
	
	$page  .= '</div>';
	
	return $page;
}

/*
** -----------------
** MISSIONS SUBMENU
** -----------------
*/

function warquest_menu_mission() {

	/* input */
	global $mid;
	global $sid;
	global $player;
	global $config;
	global $player;
		
	/* workarround of existing players */
	if (($player->lid>0) && ($sid==0)) {
		$sid=1;
	}
			
	$query  = 'select mgid from mission_group where planet='.$player->planet;
	$query .= ' and mgid!=0 order by mgid';
	
	$result = warquest_db_query($query);	
	
	$page  = '<div class="submenu">';
	
	if ($player->lid==0) {
	
		/* Training Missions */	
		$page .= warquest_ui_menu($mid, 0, 0, t('MISSION_GROUP_0'), $sid);
	
	} else {
	
		while ($data=warquest_db_fetch_object($result)) {
	
			$page .= warquest_ui_menu($mid, $data->mgid, 0, t('MISSION_GROUP_'.$data->mgid), $sid);

		}
	}
	
	$page  .= '</div>';
	
	return $page;
}

/*
** -----------------
** BATTLE SUBMENU
** -----------------
*/

function warquest_menu_battle() {

	/* input */
	global $mid;
	global $sid;
	 
	$page  = '<div class="submenu">';
	 
	$page .= warquest_ui_menu($mid, PAGE_ENEMIES, 0, t('BATTLE_ENEMIES'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_BOUNTY, 0, t('BATTLE_BOUNTY'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_CLAN_WAR, 0, t('BATTLE_CLAN_WAR'), $sid);
		
	$page  .= '</div>';
		
	return $page;
}

/*
** -----------------
** UNITS SUBMENU
** -----------------
*/

function warquest_menu_unit() {

	/* input */
	global $mid;
	global $sid;
	global $player;
	
	$page  = '<div class="submenu">';
	
	$query  = 'select ugid, type from unit_group where planet='.$player->planet.' and type!=0 and type!=6 order by type';
	$result = warquest_db_query($query);	
	
	while ($data=warquest_db_fetch_object($result)) {
			
		$page .= warquest_ui_menu($mid, $data->ugid, 0, t('UNIT_GROUP_'.$data->ugid), $sid);
	
	}

	$page .= '</div>';

	return $page;
}

/*
** --------------------
** BUILDINGS SUBMENU
** --------------------
*/

function warquest_menu_building() {

	/* input */
	global $mid;		
	global $sid;
	global $player;
	
	$query2 = 'select ugid from unit_group where type=2 and planet='.$player->planet;
	$result2 = warquest_db_query($query2);
	$data2 = warquest_db_fetch_object($result2);
			
	$query  = 'select bgid, type from building_group where ';
	$query .= 'planet='.$player->planet.' ';	
	$query .= 'order by bgid';
		
	$result = warquest_db_query($query);	
	
	$page  = '<div class="submenu">';
		
	while ($data = warquest_db_fetch_object($result)) {
	
		$ssid=0;
		if ($data->type==2) {
			$ssid = $data2->ugid;
		}
		$page .= warquest_ui_menu($mid, $data->bgid, $ssid, t('BUILDING_GROUP_'.$data->bgid), $sid);
	}
	$page .= '</div>';
	
	return $page;
}

function warquest_subsubmenu_building() {

	/* input */
	global $mid;		
	global $sid;
	global $ssid;
	global $player;

	$page  = '<div class="submenu">';
				
	$query  = 'select ugid from unit_group where planet='.$player->planet.' and type!=0 and type!=6 order by type';
	$result = warquest_db_query($query);	
	
	while ($data = warquest_db_fetch_object($result)) {
			
		$page .= warquest_ui_subsubmenu($mid, $sid, $data->ugid, t('UNIT_GROUP_'.$data->ugid), $ssid);

	}
	
	$page .= '</div>';

	return $page;
}


/*
** --------------------
** MONEY SUBMENU
** --------------------
*/

function warquest_menu_money() {

	/* input */
	global $mid;
	global $sid;
	global $cid;
		
	$page  = '<div class="submenu">';
		
	$page  = warquest_ui_menu($mid, PAGE_BANK, 0, t('LINK_BANK'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_STOCK_EXCHANGE, 0, t('LINK_STOCKEXCHANGE'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_CASINO, 0, t('LINK_CASINO'), $sid);
	
	$page .= ' | ';
	
	switch ( $sid ) { 
	
		case PAGE_BANK: 
			$tmp = array(1, 2, 3);
			foreach ($tmp as $id) {
	
				$menu = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$id, t('BANK_GROUP_'.$id), t('BANK_GROUP_'.$id));
				if ($id==$cid) {
					$menu = '<b>'.$menu.'</b>';
				} 
				$page .= $menu.' ';
			}
			break;
		
		case PAGE_STOCK_EXCHANGE: 
			$tmp = array(1, 2, 3, 4);
			foreach ($tmp as $id) {
	
				$menu = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$id, t('STOCK_GROUP_'.$id), t('STOCK_GROUP_'.$id));
				if ($id==$cid) {
					$menu = '<b>'.$menu.'</b>';
				} 
				$page .= $menu.' ';
			}
			break;
			
		case PAGE_CASINO:
			$menu = warquest_link('mid='.$mid.'&sid='.$sid.'&cid=1', t('CASINO_1'), 'casino1');
			if ($cid==1) {
				$menu = '<b>'.$menu.'</b>';
			} 
			$page .= $menu.' ';
	
			$menu = warquest_link('mid='.$mid.'&sid='.$sid.'&cid=2', t('CASINO_2'), 'casino2');
			if ($cid==2) {
				$menu = '<b>'.$menu.'</b>';
			} 
			$page .= $menu.' ';
			
			$menu = warquest_link('mid='.$mid.'&sid='.$sid.'&cid=3', t('CASINO_3'), 'casino3');
			if ($cid==3) {
				$menu = '<b>'.$menu.'</b>';
			} 
			$page .= $menu.' ';
			break;
	}

	$page .= '</div>';

	return $page;
}

/*
** --------------------
** ALLIANCE SUBMENU
** --------------------
*/

function warquest_menu_alliance() {

	/* input */
	global $mid;
	global $sid;
	global $player;
	
	/* Count not accepted recruit request */
	$query  = 'select pid1 from player_player where approved=0 and pid2='.$player->pid; 
	$result = warquest_db_query($query);	
	$recruit = warquest_db_num_rows($result);
	
	$page  = '<div class="submenu">';
	
	$page .= warquest_ui_menu($mid, PAGE_PENDING, 0, t('LINK_PENDING'), $sid, $recruit);
	$page .= warquest_ui_menu($mid, PAGE_INVITE, 0, t('LINK_INVITE'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_ACCEPTED, 0, t('LINK_APPROVED'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_BEST_PLAYER, 0, t('LINK_BEST_PLAYER'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_BEST_COUNTRY, 0, t('LINK_BEST_COUNTRY'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_CLAN, 0, t('LINK_CLAN'), $sid);
	
	$page .= '</div>';
	
	return $page;
}

/*
** --------------------
** FORUMS SUBMENU
** --------------------
*/

function warquest_menu_forum() {

	/* input */
	global $mid;
	global $sid;

	$page  = '<div class="submenu">';

	$page .= warquest_ui_menu($mid, PAGE_FORUM, 0, t('LINK_FORUM'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_POLL, 0, t('LINK_POLLS'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_CHATROOM, 0, t('LINK_CHATROOM'), $sid);
	
	$page .= '</div>';
	
	return $page;
}

/*
** --------------------
** HELP SUBMENU
** --------------------
*/

function warquest_menu_help() {

	/* input */
	global $mid;
	global $sid;

	$page  = '<div class="submenu">';

	$page .= warquest_ui_menu($mid, PAGE_INSTRUCTIONS, 0, t('LINK_GENERAL'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_RELEASENOTES, 0, t('LINK_NOTES'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_RANKS, 0, t('LINK_RANKS'), $sid);		
	$page .= warquest_ui_menu($mid, PAGE_AWARDS, 0, t('LINK_AWARDS'), $sid);	
	$page .= warquest_ui_menu($mid, PAGE_LEVELS, 0, t('LINK_LEVELS'), $sid);	
	$page .= warquest_ui_menu($mid, PAGE_STATS, 0, t('LINK_STATS'), $sid);	
	$page .= warquest_ui_menu($mid, PAGE_DONATE, 0, t('LINK_DONATE'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_ABOUT, 0, t('LINK_ABOUT'), $sid);
	
	$page .= '</div>';
	
	return $page;
}

/*
** --------------------
** ADMIN SUBMENU
** --------------------
*/

function warquest_menu_admin() {

	/* input */
	global $mid;
	global $sid;
		
	$page  = '<div class="submenu">';
		
	$page .= warquest_ui_menu($mid, PAGE_PLAYER_LIST, 0, 'Members', $sid);
	$page .= warquest_ui_menu($mid, PAGE_ADMIN_NEWS, 0, 'News', $sid);
	$page .= warquest_ui_menu($mid, PAGE_ADMIN_MESSAGES, 0, 'Messages', $sid);
	$page .= warquest_ui_menu($mid, PAGE_LEVEL, 0, 'Levels', $sid);
	$page .= warquest_ui_menu($mid, PAGE_BROWSER, 0, 'Browsers', $sid);
	$page .= warquest_ui_menu($mid, PAGE_INFO, 0, 'Info', $sid);
	$page .= warquest_ui_menu($mid, PAGE_ACTIONS, 0, 'Actions', $sid);

	$page .= '</div>';

	return $page;
}

/*
** ---------
** SUBMENU
** ---------
*/

function warquest_ui_submenu() {

	/* input */
	global $mid;
		
	switch ($mid) {
				
		case MENU_HOME:
				$page = warquest_menu_home();
				break;

		case MENU_MISSIONS:
				$page = warquest_menu_mission();
				break;

		case MENU_BATTLE:
				$page = warquest_menu_battle();
				break;

		case MENU_UNITS:
				$page = warquest_menu_unit();
				break;

		case MENU_BUILDINGS:
				$page = warquest_menu_building();
				break;

		case MENU_MONEY:
				$page = warquest_menu_money();
				break;

		case MENU_ALLIANCE:
				$page = warquest_menu_alliance();
				break;

		case MENU_FORUMS:			
				$page = warquest_menu_forum();
				break;
			
		case MENU_HELP:
				$page = warquest_menu_help();
				break;
				
		case MENU_ADMIN:
				$page = warquest_menu_admin();
				break;	
	}
	
	return $page;
}

/*
** ---------
** THE END
** ---------
*/

?>