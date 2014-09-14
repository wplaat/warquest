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
 * Sector generated by hbm2java
 */
@Entity
@Table(name="sector"
    ,catalog="warquest"
)
public class Sector  implements java.io.Serializable {


     private Integer sid;
     private int x;
     private int y;
     private Integer cid;
     private int planet;
     private int damage;
     private Date conquerDate;
     private int mid;

    public Sector() {
    }

	
    public Sector(int x, int y, int planet, int damage, Date conquerDate, int mid) {
        this.x = x;
        this.y = y;
        this.planet = planet;
        this.damage = damage;
        this.conquerDate = conquerDate;
        this.mid = mid;
    }
    public Sector(int x, int y, Integer cid, int planet, int damage, Date conquerDate, int mid) {
       this.x = x;
       this.y = y;
       this.cid = cid;
       this.planet = planet;
       this.damage = damage;
       this.conquerDate = conquerDate;
       this.mid = mid;
    }
   
     @Id @GeneratedValue(strategy=IDENTITY)
    
    @Column(name="sid", nullable=false)
    public Integer getSid() {
        return this.sid;
    }
    
    public void setSid(Integer sid) {
        this.sid = sid;
    }
    
    @Column(name="x", nullable=false)
    public int getX() {
        return this.x;
    }
    
    public void setX(int x) {
        this.x = x;
    }
    
    @Column(name="y", nullable=false)
    public int getY() {
        return this.y;
    }
    
    public void setY(int y) {
        this.y = y;
    }
    
    @Column(name="cid")
    public Integer getCid() {
        return this.cid;
    }
    
    public void setCid(Integer cid) {
        this.cid = cid;
    }
    
    @Column(name="planet", nullable=false)
    public int getPlanet() {
        return this.planet;
    }
    
    public void setPlanet(int planet) {
        this.planet = planet;
    }
    
    @Column(name="damage", nullable=false)
    public int getDamage() {
        return this.damage;
    }
    
    public void setDamage(int damage) {
        this.damage = damage;
    }
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name="conquer_date", nullable=false, length=19)
    public Date getConquerDate() {
        return this.conquerDate;
    }
    
    public void setConquerDate(Date conquerDate) {
        this.conquerDate = conquerDate;
    }
    
    @Column(name="mid", nullable=false)
    public int getMid() {
        return this.mid;
    }
    
    public void setMid(int mid) {
        this.mid = mid;
    }




}

