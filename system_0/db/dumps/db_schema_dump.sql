--
-- PostgreSQL database dump
--

-- Dumped from database version 9.5.2
-- Dumped by pg_dump version 9.5.2

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: tasks; Type: TABLE; Schema: public; Owner: gavran
--

CREATE TABLE tasks (
    id integer NOT NULL,
    username text DEFAULT 'anonymous'::text,
    status text,
    locations real[]
);


ALTER TABLE tasks OWNER TO gavran;

--
-- Name: tasks_id_seq; Type: SEQUENCE; Schema: public; Owner: gavran
--

CREATE SEQUENCE tasks_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE tasks_id_seq OWNER TO gavran;

--
-- Name: tasks_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: gavran
--

ALTER SEQUENCE tasks_id_seq OWNED BY tasks.id;


--
-- Name: turtlebot_agents; Type: TABLE; Schema: public; Owner: gavran
--

CREATE TABLE turtlebot_agents (
    id integer NOT NULL,
    name text,
    location real[],
    time_created timestamp without time zone DEFAULT now(),
    time_modified timestamp without time zone DEFAULT now(),
    available boolean DEFAULT true
);


ALTER TABLE turtlebot_agents OWNER TO gavran;

--
-- Name: turtlebot_agents_id_seq; Type: SEQUENCE; Schema: public; Owner: gavran
--

CREATE SEQUENCE turtlebot_agents_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE turtlebot_agents_id_seq OWNER TO gavran;

--
-- Name: turtlebot_agents_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: gavran
--

ALTER SEQUENCE turtlebot_agents_id_seq OWNED BY turtlebot_agents.id;


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: gavran
--

ALTER TABLE ONLY tasks ALTER COLUMN id SET DEFAULT nextval('tasks_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: gavran
--

ALTER TABLE ONLY turtlebot_agents ALTER COLUMN id SET DEFAULT nextval('turtlebot_agents_id_seq'::regclass);


--
-- Name: tasks_pkey; Type: CONSTRAINT; Schema: public; Owner: gavran
--

ALTER TABLE ONLY tasks
    ADD CONSTRAINT tasks_pkey PRIMARY KEY (id);


--
-- Name: turtlebot_agents_name_key; Type: CONSTRAINT; Schema: public; Owner: gavran
--

ALTER TABLE ONLY turtlebot_agents
    ADD CONSTRAINT turtlebot_agents_name_key UNIQUE (name);


--
-- Name: turtlebot_agents_pkey; Type: CONSTRAINT; Schema: public; Owner: gavran
--

ALTER TABLE ONLY turtlebot_agents
    ADD CONSTRAINT turtlebot_agents_pkey PRIMARY KEY (id);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

