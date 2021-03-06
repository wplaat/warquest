package nl.warquest.database.entity;
// Generated 18-mrt-2014 21:03:36 by Hibernate Tools 3.2.2.GA


import javax.persistence.AttributeOverride;
import javax.persistence.AttributeOverrides;
import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.Table;

/**
 * Views generated by hbm2java
 */
@Entity
@Table(name="views"
    ,catalog="warquest"
)
public class Views  implements java.io.Serializable {


     private ViewsId id;
     private int requests;

    public Views() {
    }

    public Views(ViewsId id, int requests) {
       this.id = id;
       this.requests = requests;
    }
   
     @EmbeddedId
    
    @AttributeOverrides( {
        @AttributeOverride(name="mid", column=@Column(name="mid", nullable=false) ), 
        @AttributeOverride(name="sid", column=@Column(name="sid", nullable=false) ), 
        @AttributeOverride(name="ssid", column=@Column(name="ssid", nullable=false) ), 
        @AttributeOverride(name="eid", column=@Column(name="eid", nullable=false) ) } )
    public ViewsId getId() {
        return this.id;
    }
    
    public void setId(ViewsId id) {
        this.id = id;
    }
    
    @Column(name="requests", nullable=false)
    public int getRequests() {
        return this.requests;
    }
    
    public void setRequests(int requests) {
        this.requests = requests;
    }




}


