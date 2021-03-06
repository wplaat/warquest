package nl.warquest.database.entity;
// Generated 18-mrt-2014 21:03:36 by Hibernate Tools 3.2.2.GA


import java.util.Date;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import static javax.persistence.GenerationType.IDENTITY;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

/**
 * Statistics generated by hbm2java
 */
@Entity
@Table(name="statistics"
    ,catalog="warquest"
)
public class Statistics  implements java.io.Serializable {


     private Integer id;
     private Date date;
     private int requests;
     private int fights;
     private int players;
     private int logins;
     private int missions;
     private int gold;
     private int casino;

    public Statistics() {
    }

    public Statistics(Date date, int requests, int fights, int players, int logins, int missions, int gold, int casino) {
       this.date = date;
       this.requests = requests;
       this.fights = fights;
       this.players = players;
       this.logins = logins;
       this.missions = missions;
       this.gold = gold;
       this.casino = casino;
    }
   
     @Id @GeneratedValue(strategy=IDENTITY)
    
    @Column(name="id", nullable=false)
    public Integer getId() {
        return this.id;
    }
    
    public void setId(Integer id) {
        this.id = id;
    }
    @Temporal(TemporalType.DATE)
    @Column(name="date", nullable=false, length=10)
    public Date getDate() {
        return this.date;
    }
    
    public void setDate(Date date) {
        this.date = date;
    }
    
    @Column(name="requests", nullable=false)
    public int getRequests() {
        return this.requests;
    }
    
    public void setRequests(int requests) {
        this.requests = requests;
    }
    
    @Column(name="fights", nullable=false)
    public int getFights() {
        return this.fights;
    }
    
    public void setFights(int fights) {
        this.fights = fights;
    }
    
    @Column(name="players", nullable=false)
    public int getPlayers() {
        return this.players;
    }
    
    public void setPlayers(int players) {
        this.players = players;
    }
    
    @Column(name="logins", nullable=false)
    public int getLogins() {
        return this.logins;
    }
    
    public void setLogins(int logins) {
        this.logins = logins;
    }
    
    @Column(name="missions", nullable=false)
    public int getMissions() {
        return this.missions;
    }
    
    public void setMissions(int missions) {
        this.missions = missions;
    }
    
    @Column(name="gold", nullable=false)
    public int getGold() {
        return this.gold;
    }
    
    public void setGold(int gold) {
        this.gold = gold;
    }
    
    @Column(name="casino", nullable=false)
    public int getCasino() {
        return this.casino;
    }
    
    public void setCasino(int casino) {
        this.casino = casino;
    }




}


