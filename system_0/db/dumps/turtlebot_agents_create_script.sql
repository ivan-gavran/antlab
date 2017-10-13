-- Table: turtlebot_agents

-- DROP TABLE turtlebot_agents;

CREATE TABLE turtlebot_agents
(
  id serial NOT NULL,
  name text,
  time_created timestamp without time zone DEFAULT now(),
  time_modified timestamp without time zone DEFAULT now(),
  available boolean DEFAULT true,
  location point,
  CONSTRAINT turtlebot_agents_pkey PRIMARY KEY (id),
  CONSTRAINT turtlebot_agents_name_key UNIQUE (name)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE turtlebot_agents
  OWNER TO gavran;
