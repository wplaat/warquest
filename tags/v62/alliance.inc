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
** ----------
** PARAMETERS
** ----------
*/

$clan = warquest_post('clan', '');
$slogan = warquest_post('slogan', '');
	
/*
** ---------------------
** Invite
** ---------------------
*/

function warquest_alliance_invite_do() {

	/* output */ 
	global $player;
	global $other;
	global $popup;
	global $config;
	
	$query  = 'select pid1 from player_player where ';
	$query .= '(pid1='.$player->pid.' and pid2='.$other->pid.') or '; 
	$query .= '(pid1='.$other->pid.' and pid2='.$player->pid.')'; 
	$result = warquest_db_query($query);	
	
	$count=warquest_db_num_rows($result);
	
	if (($player->alliance + $player->invite) >= $player->lid*$config["max_ally_factor"]) {
		
		/* Skip action. Max size */
		
	} else if ($count==0) {
	
		warquest_db_alliance_insert($player->pid, $other->pid, 0);	

		$player->invite = warquest_db_invite_size($player->pid);				
		$other->invite = warquest_db_invite_size($other->pid);
	
		warquest_alliance_invite_mail($other->pid, $player->name);
		
		$message = t('ALLIANCE_INVITATION', $other->name);
		$popup .= warquest_box_icon("info", $message);
	}
}

/**
 * Invite friend form
 */
function warquest_alliance_invite_form() {

	/* input */
	global $config;
	global $player;
	global $mid;
	global $sid;
	global $myemail;
	global $offset;
	
	/* output */
	global $page;
	global $title;
	global $sort;
	
	$title = t('ALLIANCE_INVITE_TITLE1');
			
	$page .= '<div class="subparagraph">';
	$page .= t('ALLIANCE_INVITE_TITLE2', $player->alliance, $player->invite);
	$page .= '</div>';

	if ($player->lid==0) {
		
		$page .= '<br/>';
	
		$title = "";
		$message  = '<table>';
		
		$message .= '<tr>';
		
		$message .= '<td>';
		$message .= warquest_image("other/unlock.png");
		$message .= '</td>';
		
		$message .= '<td>';
		$message .= t('ALLIANCE_LOCKED');
		$message .= '</td>';
		
		$message .= '</tr>';
		
		$message .= '</table>';

		$page .= warquest_box($title, $message);
	
	} else if (($player->alliance + $player->invite) >= $player->lid*$config["max_ally_factor"]) {
		
		$message = t('ALLIANCE_MAXIMUM', $player->lid * $config["max_ally_factor"]);
		$page .= warquest_box_icon("info", $message);
	
	} else {
		
		$limit = 50;	
		
		$query  = 'select pid from player where pid not in ';
		$query .= '(select pid2 from player_player where pid1='.$player->pid.') and pid!='.$player->pid.' ';
		$query .= 'and (alliance+invite)<(lid*'.$config["max_ally_factor"].') ';
		$result = warquest_db_query($query);	 
		$total = warquest_db_num_rows($result);
		
		/* Show all not recruited players */
		$query  = 'select pid, name, country, lid, experience, alliance, request_date ';
		$query .= 'from player where pid not in ';
		$query .= '(select pid2 from player_player where pid1='.$player->pid.') and pid!='.$player->pid.' ';
		$query .= 'and (alliance+invite)<(lid*'.$config["max_ally_factor"].') ';
	
		switch ($sort) {
		
			case 1:
				$query .= 'order by country asc ';
				break;
				
			case 2:
				$query .= 'order by name asc ';
				break;
			
			default:	
			case 3:
				$query .= 'order by request_date desc ';
				break;
				
			case 4:
				$query .= 'order by lid desc, experience desc ';
				break;

			case 5:
				$query .= 'order by experience desc ';
				break;
				
			case 6:
				$query .= 'order by alliance desc ';
				break;		
		}
		
		$query .= 'limit '.$offset.','.$limit;
		$result = warquest_db_query($query);	
	
		$page .= '<div class="box">';
		
		$page .= warquest_page_control($offset, $limit, $total, 1, '&sort='.$sort);
	
		$page .= '<table>';
		
		$page .= '<tr>';
		$page .= '<th width="50">';
		$page .= '</th>';
		
		$page .= '<th width="130">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=2', t('GENERAL_PLAYER'));
		$page .= '</th>';
		
		$page .= '<th width="70">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=3', t('GENERAL_ACTIVE'));
		$page .= '</th>';
				
		$page .= '<th width="50">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=4', t('GENERAL_LEVEL'));
		$page .= '</th>';
		
		$page .= '<th width="90">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=5', t('GENERAL_EXP'));
		$page .= '</th>';
		
		$page .= '<th width="60">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=6', t('GENERAL_ALLIANCE'));
		$page .= '</th>';
		
		$page .= '<th width="50">';
		$page .= '</th>';
		
		$page .= '</tr>';
		
		$count=0;
	
		while ($data=warquest_db_fetch_object($result)) {
		
			$page .= '<tr>';
			
			$page .= '<td>';
			$page .= warquest_flag_image($data->country);
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$data->pid, $data->name);
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_ui_ago($data->request_date);
			$page .= '</td>';					
			
			$page .= '<td>';
			$page .= $data->lid;
			$page .= '</td>';		
			
			$page .= '<td>';
			$page .= number_format($data->experience,0,",",".");
			$page .= '</td>';			
			
			$page .= '<td>';
			$page .= $data->alliance;
			$page .= '</td>';			
			
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$data->pid.'&eid='.EVENT_ALLIANCE_INVITE.'&sort='.$sort.'&offset='.$offset, t('LINK_RECRUIT'), "recuit".$count++);
			$page .= '</td>';
			
			$page .= '</tr>';
		}
		
		$page .= '</table>';
		$page .= warquest_page_control($offset, $limit, $total, 0, '&sort='.$sort);	
		$page .= '</div>';			
	} 

	$page .= '<div class="note">';
	$page .= t('ALLIANCE_INVITE_NOTE', $player->lid * $config["max_ally_factor"]);
   $page .= '</div>';		
}

/*
** ---------------------
** Pending and Approved
** ---------------------
*/
	
function warquest_alliance_drop_do() {

	/* input */	
	global $player;
	global $other;
	
		/* output */
	global $popup;
	
	warquest_db_alliance_delete($player->pid, $other->pid);
	warquest_db_alliance_delete($other->pid, $player->pid);

	/* Update attack and defense value */
	$player->alliance = warquest_db_alliance_size($player->pid);
	$player->invite = warquest_db_invite_size($player->pid);
	
	$other->alliance = warquest_db_alliance_size($other->pid);
	$other->invite = warquest_db_invite_size($other->pid);
		
	warquest_alliance_drop_mail($other->pid, $player->name);
	
	$message = t('ALLIANCE_DROP', $other->name);
	$popup .= warquest_box_icon("info", $message);
}
				
function warquest_alliance_reject_do() {

	/* input */
	global $player;
	global $other;
	
	/* output */
	global $popup;
	
	warquest_db_alliance_delete($player->pid, $other->pid);
	warquest_db_alliance_delete($other->pid, $player->pid);

	/* Update attack and defense value */
	$player->alliance = warquest_db_alliance_size($player->pid);
	$player->invite = warquest_db_invite_size($player->pid);
	
	$other->alliance = warquest_db_alliance_size($other->pid);
	$other->invite = warquest_db_invite_size($other->pid);
		
	warquest_alliance_reject_mail($other->pid, $player->name);
	
	$message = t('ALLIANCE_REJECT', $other->name);
	$popup .= warquest_box_icon("info", $message);
}
	
function warquest_alliance_accept_do() {

	/* output */
	global $player;
	global $other;
	
	/* output */
	global $popup;
	
	$query  = 'select pid1 from player_player where pid1='.$player->pid.' and pid2='.$other->pid;
	$result = warquest_db_query($query);	
	$count=warquest_db_num_rows($result);
	
	if ($count==0) {
		/* Create alliance connection $player -> $other */
		warquest_db_alliance_insert($player->pid, $other->pid, 1);
	}
	warquest_db_alliance_update($other->pid, $player->pid, 1);
		
	/* Update attack and defense value */
	$player->alliance = warquest_db_alliance_size($player->pid);
	$player->invite = warquest_db_invite_size($player->pid);
	
	$other->alliance = warquest_db_alliance_size($other->pid);
	$other->invite = warquest_db_invite_size($other->pid);
		
	warquest_alliance_accept_mail($other->pid, $player->name);
	
	$message = t('ALLIANCE_ACCEPT',$other->name); 
	$popup .= warquest_box_icon("info", $message);
}

function warquest_alliance_accepted_form() {

	/* input */	
	global $mid;
	global $sid;
	global $player;
	global $other;
	global $offset;
		
	/* output */
	global $page;
	global $title;
	
	$title = t('ALLIANCE_ACCEPT_TITLE1');

	$count=1;
	
	/* Get approved alliance player */
	$page .= '<div class="subparagraph">';
	$page .= t('ALLIANCE_ACCEPT_TITLE2', $player->alliance, $player->invite);
	$page .= '</div>';

	$page .= '<div class="box">';
	$page .= '<table>';
	
	$page .= '<tr>';
	
	$page .= '<th width="40">';
	$page .= t('GENERAL_NUMBER');
	$page .= '</th>';
	
	$page .= '<th width="40">';
	$page .= '</th>';
	
	$page .= '<th width="150">';
	$page .= t('GENERAL_PLAYER');
	$page .= '</th>';
	
	$page .= '<th width="100">';
	$page .= t('GENERAL_LEVEL');
	$page .= '</th>';
	
	$page .= '<th width="100">';
	$page .= t('GENERAL_APPROVED');	
	$page .= '</th>';
	
	$page .= '<th width="90">';
	$page .= '</th>';
	
	$page .= '<th width="90">';
	$page .= '</th>';
	
	$page .= '</tr>';
		
	/* Your Self */
	$page .= '<tr>';
	
	$page .= '<td>';
	$page .= $count++;
	$page .= '</td>';
	
	$page .= '<td>';
	$page .= warquest_flag_image($player->country);
	$page .= '</td>';
	
	$page .= '<td>';
	$page .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$player->pid, $player->name);
	$page .= '</td>';
	
	$page .= '<td>';
	$page .= $player->lid;
	$page .= '</td>';
	
	$page .= '<td>';
	$page .= t('GENERAL_YES');
	$page .= '</td>';		
	
	$page .= '<td>';
	$page .= '</td>';
	
	$page .= '<td>';
	$page .= '</td>';
	
	$page .= '</tr>';
	
	$limit = 50;	
		
	$query = 'select pid1 from player_player where pid1='.$player->pid.' and approved=1';
	$result = warquest_db_query($query);	 
	$total = warquest_db_num_rows($result);
		
	/* Get approved alliance players */
	$query  = 'select b.country, b.name, b.lid, a.pid1, a.pid2, a.approved ';
	$query .= 'from player_player a, player b where b.pid=a.pid2 and a.pid1='.$player->pid.' '; 
	$query .= 'and a.approved=1 order by b.lid desc, b.pid ';
	$query .= 'limit '.$offset.','.$limit;
	$result = warquest_db_query($query);	 
	
	$size=warquest_db_num_rows($result);
	
	$page .= warquest_page_control($offset, $limit, $total, 1);
	
	$count = $offset+2;
	
	if ($size>0) {
	
		$page .= '<tr>';
		
		$page .= '<td colspan="7">';
		$page .= '<hr>';
		$page .= '</td>';
	
		$page .= '</tr>';
	
		while ($data=warquest_db_fetch_object($result)) {
	
			$page .= '<tr>';
			
			$page .= '<td>';
			if ($data->approved==1) {
				$page .= $count++;
			}
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_flag_image($data->country);
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$data->pid2, $data->name);
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= $data->lid;
			$page .= '</td>';
			
			$page .= '<td>';
			if ($data->approved==0) {
				$page .= t('GENERAL_NO');
			} else {
				$page .= t('GENERAL_YES');
			}
			$page .= '</td>';		
			
			$page .= '<td>';
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$data->pid2.'&eid='.EVENT_ALLIANCE_DROP.'&offset='.$offset, t('LINK_DROP') ,"drop".$count);
			$page .= '</td>';
			
			$page .= '</tr>';
		}
	}
		
	$page .= '</table>';
	$page .= warquest_page_control($offset, $limit, $total, 0);	
	$page .= '</div>';
	
	$page .= '<div class="note">';
	$page .= t('ALLIANCE_NOTE');
   $page .= '</div>';	
}

function warquest_alliance_pending_form() {

	/* input */	
	global $mid;
	global $sid;
	
	global $player;
	global $other;
		
	/* output */
	global $page;
	global $title;
	
	$title = t('ALLIANCE_PENDING_TITLE1');

	$count = 1;
	$flag = 0;
	$tmp1 = "";
	$tmp2 = "";
	
	/* Get pending alliance player */
	$page .= '<div class="subparagraph">';
	$page .= t('ALLIANCE_PENDING_TITLE2', $player->alliance, $player->invite);
	$page .= '</div>';

	/* Show not approved alliance */
	$query  = 'select b.country, b.name, b.lid, a.pid1, a.pid2, a.approved ';
	$query .= 'from player_player a, player b where a.pid1=b.pid and a.pid2='.$player->pid.' '; 
	$query .= 'and a.approved=0';
	$result = warquest_db_query($query);	 
	
	$size=warquest_db_num_rows($result);
	
	if ($size>0) {
	
		$flag = 1;
			
		while ($data=warquest_db_fetch_object($result)) {
		
			$tmp1 .= '<tr>';
			
			$tmp1 .= '<td>';
			$tmp1 .= $count++;		
			$tmp1 .= '</td>';
			
			$tmp1 .= '<td>';
			$tmp1 .= warquest_flag_image($data->country);
			$tmp1 .= '</td>';
			
			$tmp1 .= '<td>';
			$tmp1 .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$data->pid1, $data->name);
			$tmp1 .= '</td>';
			
			$tmp1 .= '<td>';
			$tmp1 .= $data->lid;
			$tmp1 .= '</td>';
			
			$tmp1 .= '<td>';
			$tmp1 .= t('GENERAL_NO');
			$tmp1 .= '</td>';	
	
			$tmp1 .= '<td>';
			$tmp1 .= warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$data->pid1.'&eid='.EVENT_ALLIANCE_REJECT, t('LINK_REJECT'), "reject");
			$tmp1 .= '</td>';
			
			$tmp1 .= '<td>';
			$tmp1 .= warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$data->pid1.'&eid='.EVENT_ALLIANCE_ACCEPT, t('LINK_ACCEPT'), "accept");
			$tmp1 .= '</td>';
			
			$tmp1 .= '</tr>';
		}
		
		$tmp1 .= '<tr>';
		$tmp1 .= '<td colspan="7">';
		$tmp1 .= '<hr>';
		$tmp1 .= '</td>';
		$tmp1 .= '</tr>';
	}
		
	/* Get not approved alliance players */
	$query  = 'select b.country, b.name, b.lid, a.pid1, a.pid2, a.approved ';
	$query .= 'from player_player a, player b where b.pid=a.pid2 and a.pid1='.$player->pid.' '; 
	$query .= 'and a.approved=0 order by b.lid desc';
	$result = warquest_db_query($query);	 
	
		$size=warquest_db_num_rows($result);
	
	if ($size>0) {
	
		$flag = 1;
		
		while ($data=warquest_db_fetch_object($result)) {
	
			$tmp2 .= '<tr>';
			
			$tmp2 .= '<td>';
			$tmp2 .= $count++;
			$tmp2 .= '</td>';
			
			$tmp2 .= '<td>';
			$tmp2 .= warquest_flag_image($data->country);
			$tmp2 .= '</td>';
			
			$tmp2 .= '<td>';
			$tmp2 .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$data->pid2, $data->name);
			$tmp2 .= '</td>';
			
			$tmp2 .= '<td>';
			$tmp2 .= $data->lid;
			$tmp2 .= '</td>';
			
			$tmp2 .= '<td>';
			if ($data->approved==0) {
				$tmp2 .= t('GENERAL_NO');
			} else {
				$tmp2 .= t('GENERAL_YES');
			}
			$tmp2 .= '</td>';	
	
			$tmp2 .= '<td>';
			$tmp2 .= '</td>';
			
			$tmp2 .= '<td>';
			$tmp2 .= warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$data->pid2.'&eid='.EVENT_ALLIANCE_DROP, t('LINK_DROP') ,"drop".$count);
			$tmp2 .= '</td>';
			
			$tmp2 .= '</tr>';
		}
	}
	
	if ($flag == 0) {
	
		$message = t('ALLIANCE_NO_PENDING');
		$page .= warquest_box_icon("info", $message);
		
	} else {
			
		$page .= '<div class="box">';
		$page .= '<table>';
	
		$page .= '<tr>';
		
		$page .= '<th width="40">';
		$page .= t('GENERAL_NUMBER');
		$page .= '</th>';
		
		$page .= '<th width="40">';
		$page .= '</th>';
		
		$page .= '<th width="150">';
		$page .= t('GENERAL_PLAYER');
		$page .= '</th>';
		
		$page .= '<th width="100">';
		$page .= t('GENERAL_LEVEL');
		$page .= '</th>';
		
		$page .= '<th width="100">';
		$page .= t('GENERAL_APPROVED');	
		$page .= '</th>';
		
		$page .= '<th width="90">';
		$page .= '</th>';
		
		$page .= '<th width="90">';
		$page .= '</th>';
		
		$page .= '</tr>';
		
		$page .= $tmp1;
		$page .= $tmp2;
		
		$page .= '</table>';
		
		$page .= '</div>';
	}
	
	$page .= '<div class="note">';
	$page .= t('ALLIANCE_NOTE');
   $page .= '</div>';	
}

/*
** --------------
** ACTIONS
** --------------
*/

/**
 * Commandor of clan can drop a member.
 */
function warquest_clan_drop_do() {

	/* input */
	global $player;
	global $other;
	global $cid;
		
	/* output */
	global $popup;	

	$player_clan = warquest_db_player_clan($other->pid);
	
	if ($player_clan->cid!=$cid) {
		
		$message = t('CLAN_NOT_PART');
		$popup .= warquest_box_icon("warning", $message);
		
	} else {
		
		warquest_db_player_clan_delete($other->pid, $cid);
	
		/* Update player netto income */		
		warquest_netto_income($other);
	
		$message = t('CLAN_DROP');
		$popup .= warquest_box_icon("info", $message);
	
	}
}

/**
 * Member can leave a clan 
 */
function warquest_clan_leave_do() {

	/* input */
	global $player;
	global $cid;
		
	/* output */
	global $popup;	

	$player_clan = warquest_db_player_clan($player->pid);
	
	if (!isset($player_clan->cid) ) {
		
		$message = t('CLAN_NOT_PART');
		$popup .= warquest_box_icon("warning", $message);
		
	} else {
		
		warquest_db_player_clan_delete($player->pid, $cid);
		
		/* Update player netto income */		
		warquest_netto_income($player);
	
		$message = t('CLAN_LEAVE');
		$popup .= warquest_box_icon("info", $message);
	
	}
}

/**
 * Member can join a clan
 */
function warquest_clan_join_do() {

	/* input */
	global $player;
	global $cid;
		
	/* output */
	global $popup;	

	$player_clan = warquest_db_player_clan($player->pid);
	
	if ( isset($player_clan->cid) ) {
		
		$message = t('CLAN_ALL_PART');
		$popup .= warquest_box_icon("warning", $message);
		
	} else {
	
		warquest_db_player_clan_insert($player->pid, $cid);
	
		/* Update player netto income */		
		warquest_netto_income($player);
		
		$message = t('CLAN_JOINED');
		$popup .= warquest_box_icon("info", $message);
	
	}
}

function warquest_clan_slogan_do() {

	/* input */
	global $player;
	global $cid;
	global $slogan;	
		
	/* output */
	global $popup;	
	
	$clan = warquest_db_clan($cid);
	 	
	if (strlen($slogan) < 5) {
			
		$message = t('CLAN_SLOGAN_TOO_SHORT');
		$popup .= warquest_box_icon("warning", $message);

	} else if (strlen($slogan) > 200) {
			
		$message = t('CLAN_SLOGAN_TOO_LONG');
		$popup .= warquest_box_icon("warning", $message);
		
	} else {
	
		$clan->slogan = $slogan;
		
		warquest_db_clan_update($clan);
	
		$message = t('CLAN_SLOGAN_SAVED');
		$popup .= warquest_box_icon("info", $message);			
	}
}


function warquest_clan_create_do() {

	/* input */
	global $player;
	global $skill;
	global $clan;
		
	/* output */
	global $popup;	
	
	$query  = 'select cid from clan where name="'.$clan.'"'; 
	$result = warquest_db_query($query);	
	$count = warquest_db_num_rows($result);
	
	if ($skill->skill_points == 0) {
			
		$message = t('CLAN_NO_SKILL_POINT', $clan);
		$popup .= warquest_box_icon("warning", $message);
		
	} else if (strlen($clan) < 2) {
			
		$message = t('CLAN_NAME_TOO_SHORT');
		$popup .= warquest_box_icon("warning", $message);

	} else if (strlen($clan) > 5) {
			
		$message = t('CLAN_NAME_TOO_LONG');
		$popup .= warquest_box_icon("warning", $message);
		
	} else if ($count > 0) {
			
		$message = t('CLAN_NAME_EXIST', $clan);
		$popup .= warquest_box_icon("warning", $message);
		
	} else {
	
		$cid = warquest_db_clan_insert($player->pid, $clan);
		
		warquest_db_player_clan_insert($player->pid, $cid);
		
		$skill->skill_points--;
		warquest_db_skill_update($skill);
	
		$message = t('CLAN_CREATED', $clan);
		$popup .= warquest_box_icon("info", $message);			
	}
}

/*
** --------------
** UI
** --------------
*/

function warquest_clan_form() {

	/* input */	
	global $mid;
	global $sid;
	global $cid;
	
	global $player;
	global $other;
		
	/* output */
	global $page;
	global $title;
	
	$lid = 15;
	
	$title = t('CLAN_TITLE');

	$player_clan = warquest_db_player_clan($player->pid);
	
	/* Get pending alliance player */
	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_TITLE');
	$page .= '</div>';
	
	if ($player->lid >= $lid) {
	
		$page .= '<div class="box">';
		$page .= t('CLAN_CREATE').':';	
		$page .= ' ';	
		$page .= '<input name="clan" type="text" id="clan" size="10" maxlength="5" onkeydown="if (event.keyCode == 13) return false"/>';	
		$page .= ' ';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid='.EVENT_CLAN_CREATE, t('CLAN_ADD'), 'add');
		$page .= '</div>';
		
		$page .= '<div class="note">';
		$page .= t('CLAN_CREATE_NOTE');
		$page .= '</div>';
	}
	
	$query  = 'select a.cid, a.name, a.created, a.won, a.lost, a.pid, ';
	$query .= '(select name from player where pid=a.pid) as name2, ';
	$query .= '(select country from player where pid=a.pid) as country2, ';
	$query .= '(select count(*) from player_clan where cid=a.cid) as size, ';
	$query .= '(select count(*) from player_clan d where d.cid=a.cid and d.pid='.$player->pid.') as joined ';
	$query .= 'from clan a order by a.won desc';
	
	$result = warquest_db_query($query);	 	
	$size = warquest_db_num_rows($result);
	
	if ($size == 0) {
	
		$message = t('CLAN_NO_CLANS');
		$page .= warquest_box_icon('info', $message);
		
	} else if ($player->lid < $lid) {
			
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td>';
		$message .= warquest_image("other/unlock.png");
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('BATTLE_CLAN_WAR_UNLOCKED', t('GENERAL_PLANET_1'), $lid);
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
		
		$page .= warquest_box("", $message);
		
	} else {		
	
		$page .= '<div class="box">';
	
		$page .= '<table>';
		
		$page .= '<tr>';
						
		$page .= '<th width="160">';
		$page .= t('GENERAL_NAME');
		$page .= '</th>';
		
		$page .= '<th width="60">';
		$page .= t('GENERAL_SIZE');
		$page .= '</th>';
		
		$page .= '<th width="60">';
		$page .= t('GENERAL_WON');
		$page .= '</td>';

		$page .= '<th width="60">';
		$page .= t('GENERAL_LOST');
		$page .= '</th>';		
				
		$page .= '<th width="180">';
		$page .= t('GENERAL_COMMANDER');
		$page .= '</th>';
		
		$page .= '<th width="80">';
		$page .= '</th>';
		
		$page .= '</tr>';
		
		while ($data = warquest_db_fetch_object($result)) {
		
			$page .= '<tr>';

			$page .= '<td>';
			$page .= warquest_image("other/clan.jpg", 'width="50" height="30"').' ';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_LIST.'&cid='.$data->cid, $data->name);
			$page .= '</td>';
					
			$page .= '<td>';
			$page .= $data->size;
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= number_format($data->won,0,",",".");
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= number_format($data->lost,0,",",".");
			$page .= '</td>';
									
			$page .= '<td>';
			$page .= player_format($data->pid, $data->name2, $data->country2, 1);
			$page .= '</td>';
			
			$page .= '<td>';

			if (isset($player_clan->cid)) {		
				if ($data->cid == $player_clan->cid) {
					$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN.'&cid='.$data->cid.'&eid='.EVENT_CLAN_LEAVE, t('LINK_LEAVE'));			
				}
			} else {
				$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN.'&cid='.$data->cid.'&eid='.EVENT_CLAN_JOIN, t('LINK_JOIN'));				
			} 
				
			$page .= '</td>';
			
			$page .= '</tr>';
		}
		
		$page .= '</table>';		
		$page .= '</div>';		
	} 
		
	$page .= '<div class="note">';
	$page .= t('CLAN_NOTE');
   $page .= '</div>';	
}

function warquest_clan_list_form() {

	/* input */	
	global $mid;
	global $sid;
	global $cid;
	
	global $player;
	global $other;
		
	/* output */
	global $page;
	global $title;
	
	$count = 1;
	
	$clan = warquest_db_clan($cid);
	$comment = $clan->slogan;
	
	$title = t('CLAN_LIST_TITLE', $clan->name);
		
	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_LIST_TITLE', $clan->name);
	$page .= '</div>';

	if ($clan->pid==$player->pid) {	
		
		$page .= '<div class="box">';
		
		$page .= "<script language=\"JavaScript\" type=\"text/javascript\">function limitText(limitField, limitNum) { if (limitField.value.length >= limitNum) { limitField.value = limitField.value.substring(0, limitNum); } } </script>";
					
		$page .= '<table>';
		$page .= '<tr>';
		$page .= '<td width="500">';

		$page .= t('CLAN_SLOGAN').'<br/>'; 
	
		$page .= '<textarea style="width:100%" id="slogan" name="slogan" rows="3" ';
		$page .= 'onKeyDown="limitText(this,199)">'.$comment.'</textarea><br/>';
		$page .= warquest_show_smilies('slogan');
		$page .= '<br/><br/>';
	
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid='.EVENT_CLAN_SLOGAN, t('LINK_SAVE'), 'save');
		
		$page .= '</td>';
		$page .= '</tr>';
		$page .= '</table>';
		$page .= '</div>';
		
		$page .= '<div class="note">';
		$page .= t('CLAN_SLOGAN_NOTE');
		$page .= '</div>';	
				
	} else {
	
		$page .= '<div class="box">';
	
		$page .= t('CLAN_SLOGAN').'<br/>';
	
		$page .= '<div class="slogan">';
		$page .= warquest_parse_smilies($comment);
		$page .= '</div>';
		
		$page .= '</div>';
	} 
	
	$query  = 'select a.joined, b.pid, b.name, b.country, b.lid, b.experience ';
	$query .= 'from player_clan a, player b where a.pid=b.pid and a.cid='.$cid.' ';
	$query .= 'order by b.lid desc';

	$result = warquest_db_query($query);	 	
	$size = warquest_db_num_rows($result);
	
	if ($size == 0) {
	
		$message = t('CLAN_NO_MEMBERS');
		$page .= warquest_box_icon('info', $message);
	
	} else {
			
		$page .= '<div class="box">';
		
		$page .= '<table>';
		
		$page .= '<tr>';
		
		$page .= '<th width="30">';
		$page .= t('GENERAL_NR');
		$page .= '</th>';
		
		$page .= '<th width="150">';
		$page .= t('GENERAL_NAME');
		$page .= '</th>';
		
		$page .= '<th width="60">';
		$page .= t('GENERAL_LEVEL');
		$page .= '</th>';
		
		$page .= '<th width="90">';
		$page .= t('GENERAL_EXP');
		$page .= '</th>';

		$page .= '<th width="100">';
		$page .= t('GENERAL_JOINED');
		$page .= '</th>';
				
		$page .= '<th width="50">';
		$page .= '</th>';
		
		$page .= '</tr>';
		
		while ($data=warquest_db_fetch_object($result)) {
		
			$page .= '<tr>';
			
			$page .= '<td>';
			$page .= $count++;
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= player_format($data->pid, $data->name, $data->country, 1);
			$page .= '</td>';
					
			$page .= '<td>';
			$page .= $data->lid;
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= number_format($data->experience,0,",",".");
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_ui_ago($data->joined);
			$page .= '</td>';
				
			$page .= '<td>';
			if ($clan->pid == $player->pid) {			
				$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_LIST.'&cid='.$cid.'&oid='.$data->pid.'&eid='.EVENT_CLAN_DROP, t('LINK_DROP'));							
			}
			$page .= '</td>';
				
				
			$page .= '</tr>';
		}
		
		$page .= '</table>';
		
		$page .= '</div>';
	}
	
	$page .= '<div class="note">';
	$page .= t('CLAN_NOTE');
   $page .= '</div>';	
}

/*
** --------------
** HANDLER
** --------------
*/

function warquest_alliance() {

	/* input */
	global $eid;
	global $sid;
	
	global $player;
	global $other;
		
	/* Event Handler */
	switch ($eid) {
			
		case EVENT_ALLIANCE_INVITE:
			warquest_alliance_invite_do();
			break;
			
		case EVENT_ALLIANCE_ACCEPT:
			warquest_alliance_accept_do();
			break;	
			
		case EVENT_ALLIANCE_REJECT:
			warquest_alliance_reject_do();
			break;	
					
		case EVENT_ALLIANCE_DROP:
			warquest_alliance_drop_do();
			break;	
			
		case EVENT_CLAN_CREATE:
			warquest_clan_create_do();
			break;	
			
		case EVENT_CLAN_JOIN:
			warquest_clan_join_do();
			break;	
			
		case EVENT_CLAN_LEAVE:
			warquest_clan_leave_do();
			break;	
						
		case EVENT_CLAN_DROP:
			warquest_clan_drop_do();
			break;	
			
		case EVENT_CLAN_SLOGAN:
			warquest_clan_slogan_do();
			break;	
			
		case EVENT_SWITCH_PLANET: 
			warquest_switch_planet_do();
			break;
			
	}
	
	/* Page handler */
	switch ($sid) {

		case PAGE_PENDING: 
					warquest_alliance_pending_form();
				  break;

		case PAGE_INVITE: 
					warquest_alliance_invite_form();
				  break;
			  
		case PAGE_ACCEPTED: 
					warquest_alliance_accepted_form();
					break;	

		case PAGE_BEST_PLAYER:
					warquest_leaderboard1_form();
					break;
				  
		case PAGE_BEST_COUNTRY: 
					warquest_leaderboard2_form();
					break;
				  		  				  
		case PAGE_BEST_COUNTRY2: 
					warquest_leaderboard3_form();
					break; 
	  				  
		case PAGE_CLAN: 
					warquest_clan_form();
					break; 
					
		case PAGE_CLAN_LIST: 
					warquest_clan_list_form();
					break; 
	}				  
	
	warquest_player();	
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>