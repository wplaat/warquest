--
-- WarQuest v6.1 data model patch
--

-- Remove old sun stuff
DELETE FROM unit_group WHERE ugid>24;
DELETE FROM building_group WHERE bgid>20;

-- Remove players from sun, if any found
UPDATE player SET planet=0 WHERE planet=4;

-- Refactor planet numbers
UPDATE building_group SET planet=4 WHERE planet=3;
UPDATE building_group SET planet=3 WHERE planet=2;
UPDATE building_group SET planet=2 WHERE planet=1;
UPDATE building_group SET planet=1 WHERE planet=0;

UPDATE level SET planet=4 WHERE planet=3;
UPDATE level SET planet=3 WHERE planet=2;
UPDATE level SET planet=2 WHERE planet=1;
UPDATE level SET planet=1 WHERE planet=0;

UPDATE mission_group SET planet=4 WHERE planet=3;
UPDATE mission_group SET planet=3 WHERE planet=2;
UPDATE mission_group SET planet=2 WHERE planet=1;
UPDATE mission_group SET planet=1 WHERE planet=0;

UPDATE player SET planet=4 WHERE planet=3;
UPDATE player SET planet=3 WHERE planet=2;
UPDATE player SET planet=2 WHERE planet=1;
UPDATE player SET planet=1 WHERE planet=0;

UPDATE sector SET planet=4 WHERE planet=3;
UPDATE sector SET planet=3 WHERE planet=2;
UPDATE sector SET planet=2 WHERE planet=1;
UPDATE sector SET planet=1 WHERE planet=0;

UPDATE unit_group SET planet=4 WHERE planet=3;
UPDATE unit_group SET planet=3 WHERE planet=2;
UPDATE unit_group SET planet=2 WHERE planet=1;
UPDATE unit_group SET planet=1 WHERE planet=0;

UPDATE bonus SET bonus_id=4 WHERE bonus_id=3;
UPDATE bonus SET bonus_id=3 WHERE bonus_id=2;
UPDATE bonus SET bonus_id=2 WHERE bonus_id=1;
UPDATE bonus SET bonus_id=1 WHERE bonus_id=0;


update player set default_mission="", default_force="";

-- Added new cron job
INSERT INTO cron (cid, note, last_run) VALUES ('9', 'Remove inactive clan members', '');

-- patch clan table
ALTER TABLE `clan` CHANGE `date` `created` DATE NOT NULL ;
ALTER TABLE `clan` ADD `last_activity` DATE NOT NULL AFTER `created`;
update clan set last_activity=created;
ALTER TABLE player_clan CHANGE `date` `joined` DATETIME NOT NULL ;
