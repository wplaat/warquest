package nl.warquest.database.entity;
// Generated 18-mrt-2014 21:03:36 by Hibernate Tools 3.2.2.GA


import javax.persistence.AttributeOverride;
import javax.persistence.AttributeOverrides;
import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.Table;

/**
 * PlayerPoll generated by hbm2java
 */
@Entity
@Table(name="player_poll"
    ,catalog="warquest"
)
public class PlayerPoll  implements java.io.Serializable {


     private PlayerPollId id;
     private int answerId;

    public PlayerPoll() {
    }

    public PlayerPoll(PlayerPollId id, int answerId) {
       this.id = id;
       this.answerId = answerId;
    }
   
     @EmbeddedId
    
    @AttributeOverrides( {
        @AttributeOverride(name="pid", column=@Column(name="pid", nullable=false) ), 
        @AttributeOverride(name="pollId", column=@Column(name="poll_id", nullable=false) ) } )
    public PlayerPollId getId() {
        return this.id;
    }
    
    public void setId(PlayerPollId id) {
        this.id = id;
    }
    
    @Column(name="answer_id", nullable=false)
    public int getAnswerId() {
        return this.answerId;
    }
    
    public void setAnswerId(int answerId) {
        this.answerId = answerId;
    }




}


