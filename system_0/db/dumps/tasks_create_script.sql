-- Table: tasks

-- DROP TABLE tasks;

CREATE TABLE tasks
(
  id serial NOT NULL,
  username text DEFAULT 'anonymous'::text,
  status text DEFAULT 'pending'::text,
  time_created timestamp without time zone DEFAULT now(),
  time_modified timestamp without time zone DEFAULT now(),
  locations point[],
  CONSTRAINT tasks_pkey PRIMARY KEY (id)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE tasks
  OWNER TO gavran;
