package nl.warquest.database.entity;
// Generated 18-mrt-2014 21:03:36 by Hibernate Tools 3.2.2.GA


import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

/**
 * UnitGroup generated by hbm2java
 */
@Entity
@Table(name="unit_group"
    ,catalog="warquest"
)
public class UnitGroup  implements java.io.Serializable {


     private int ugid;
     private int planet;
     private int type;
     private String name;

    public UnitGroup() {
    }

    public UnitGroup(int ugid, int planet, int type, String name) {
       this.ugid = ugid;
       this.planet = planet;
       this.type = type;
       this.name = name;
    }
   
     @Id 
    
    @Column(name="ugid", nullable=false)
    public int getUgid() {
        return this.ugid;
    }
    
    public void setUgid(int ugid) {
        this.ugid = ugid;
    }
    
    @Column(name="planet", nullable=false)
    public int getPlanet() {
        return this.planet;
    }
    
    public void setPlanet(int planet) {
        this.planet = planet;
    }
    
    @Column(name="type", nullable=false)
    public int getType() {
        return this.type;
    }
    
    public void setType(int type) {
        this.type = type;
    }
    
    @Column(name="name", nullable=false, length=10)
    public String getName() {
        return this.name;
    }
    
    public void setName(String name) {
        this.name = name;
    }




}


