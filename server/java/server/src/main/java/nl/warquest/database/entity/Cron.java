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
 * Cron generated by hbm2java
 */
@Entity
@Table(name="cron"
    ,catalog="warquest"
)
public class Cron  implements java.io.Serializable {


     private Integer cid;
     private String note;
     private Date lastRun;

    public Cron() {
    }

    public Cron(String note, Date lastRun) {
       this.note = note;
       this.lastRun = lastRun;
    }
   
     @Id @GeneratedValue(strategy=IDENTITY)
    
    @Column(name="cid", nullable=false)
    public Integer getCid() {
        return this.cid;
    }
    
    public void setCid(Integer cid) {
        this.cid = cid;
    }
    
    @Column(name="note", nullable=false, length=65535)
    public String getNote() {
        return this.note;
    }
    
    public void setNote(String note) {
        this.note = note;
    }
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name="last_run", nullable=false, length=19)
    public Date getLastRun() {
        return this.lastRun;
    }
    
    public void setLastRun(Date lastRun) {
        this.lastRun = lastRun;
    }




}


