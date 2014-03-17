package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Invite.
 * @see nl.warquest.database.Invite
 * @author Hibernate Tools
 */
@Stateless
public class InviteHome {

    private static final Log log = LogFactory.getLog(InviteHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Invite transientInstance) {
        log.debug("persisting Invite instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Invite persistentInstance) {
        log.debug("removing Invite instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Invite merge(Invite detachedInstance) {
        log.debug("merging Invite instance");
        try {
            Invite result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Invite findById( Integer id) {
        log.debug("getting Invite instance with id: " + id);
        try {
            Invite instance = entityManager.find(Invite.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

